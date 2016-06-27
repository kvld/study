package expression;

import expression.exceptions.ArithmeticErrorException;
import expression.exceptions.ParserException;

public class CheckedParser implements Parser {

    enum Token {
        NUM, VARIABLE, PLUS, MINUS, MUL, DIV, OPEN_BRACKET, CLOSE_BRACKET, ABS, SQRT, POW, LOG;
    }

    private String expression;
    private Token currentToken;
    private int value;
    private char variable;
    private int pos;
    private int bracketsBalance;

    
    private void parseNumber() throws ParserException {
        StringBuilder sValue = new StringBuilder("");
        while (pos < expression.length() && Character.isDigit(expression.charAt(pos))) {
            sValue.append(expression.charAt(pos++));
        }
        try {
            value = Integer.parseUnsignedInt(sValue.toString());
        } catch (NumberFormatException e) {
            throw new ParserException("Incorrect number!");
        }
    }

    private void nextToken() throws ParserException {
        while (pos < expression.length() && Character.isWhitespace(expression.charAt(pos))) {
            pos++;
        }
        if (pos >= expression.length()) {
            return;
        }

        char symbol = expression.charAt(pos);
        // NUM
        if (Character.isDigit(symbol)) {
            currentToken = Token.NUM;
            parseNumber();
            pos--;
        } else {
            switch (symbol) {
                // Var
                case 'x':
                case 'y':
                case 'z':
                    currentToken = Token.VARIABLE;
                    variable = symbol;
                    break;
                // PLUS
                case '+':
                    currentToken = Token.PLUS;
                    break;
                //
                case '-':
                    currentToken = Token.MINUS;
                    break;
                //
                case '*':
                    if (pos < expression.length() - 1 && expression.substring(pos, pos + 2).equals("**")) {
                        currentToken = Token.POW;
                        pos++;
                    } else {
                        currentToken = Token.MUL;
                    }
                    break;
                //
                case '/':
                    if (pos < expression.length() - 1 && expression.substring(pos, pos + 2).equals("//")) {
                        currentToken = Token.LOG;
                        pos++;
                    } else {
                        currentToken = Token.DIV;
                    }
                    break;
                //
                case '(':
                    currentToken = Token.OPEN_BRACKET;
                    bracketsBalance++;
                    break;
                //
                case ')':
                    currentToken = Token.CLOSE_BRACKET;
                    bracketsBalance--;
                    break;
                // abs
                case 'a':
                    if (pos < expression.length() - 2 && expression.substring(pos, pos + 3).equals("abs")) {
                        currentToken = Token.ABS;
                        pos += 2;
                    }
                    break;
                // sqrt
                case 's':
                    if (pos < expression.length() - 3 && expression.substring(pos, pos + 4).equals("sqrt")) {
                        currentToken = Token.SQRT;
                        pos += 3;
                    }
                    break;
                default:
                    throw new ParserException("Undefined symbol: " + symbol);
            }
        }
        //System.out.println(currentToken);
        pos++;
    }

    private TripleExpression parseMultiplier() throws ParserException {
        switch (currentToken) {
            case MINUS:
                nextToken();
                TripleExpression num = parseMultiplier();
                return (value < 0 ? new Const(Integer.MIN_VALUE) : new CheckedNegate(num));
            case NUM:
                int number = value;
                nextToken();
                return new Const(number);
            case VARIABLE:
                String name = String.valueOf(variable);
                nextToken();
                return new Variable(name);
            case OPEN_BRACKET:
                nextToken();
                TripleExpression answer = parseAddSub();
                nextToken();
                return answer;
            case ABS:
                nextToken();
                return new CheckedAbs(parseMultiplier());
            case SQRT:
                nextToken();
                return new CheckedSqrt(parseMultiplier());
        }
        throw new ParserException("Undefined token!");
    }

    private TripleExpression parseSummand() throws ParserException {
        TripleExpression answer = parseMultiplier();
        while (currentToken == Token.MUL || currentToken == Token.DIV || currentToken == Token.POW || currentToken == Token.LOG) {
            Token token = currentToken;
            nextToken();
            if (token == Token.MUL) {
                answer = new CheckedMultiply(answer, parseMultiplier());
            } else if (token == Token.DIV) {
                answer = new CheckedDivide(answer, parseMultiplier());
            } else if (token == Token.POW) {
                answer = new CheckedPower(answer, parseMultiplier());
            } else if (token == Token.LOG) {
                answer = new CheckedLogarithm(answer, parseMultiplier());
            }
        }
        return answer;
    }

    private TripleExpression parseAddSub() throws ParserException {
        TripleExpression answer = parseSummand();
        while (currentToken == Token.PLUS || currentToken == Token.MINUS) {
            Token token = currentToken;
            nextToken();
            if (token == Token.PLUS) {
                answer = new CheckedAdd(answer, parseSummand());
            } else if (token == Token.MINUS) {
                answer = new CheckedSubtract(answer, parseSummand());
            }
        }
        return answer;
    }

    public static void test(String expression, int x, int y, int z) {
        CheckedParser parser = new CheckedParser();
        try {
            TripleExpression result = parser.parse(expression);
            try {
                int answer = result.evaluate(x, y, z);
                System.out.println(answer);
            } catch (ArithmeticErrorException e) {
                System.out.println(e.getMessage());
            }
        } catch (ParserException e) {
            System.out.println(e.getMessage());
        }
    }

    public TripleExpression parse(String s) throws ParserException {
        expression = s;
        pos = 0;
        bracketsBalance = 0;
        nextToken();
        TripleExpression exp = parseAddSub();
        if (pos != expression.length() || bracketsBalance != 0) {
            throw new ParserException("Parse error!");
        }
        return exp;
    }
}
