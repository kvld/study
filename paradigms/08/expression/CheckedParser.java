package expression;

import expression.exceptions.ParserException;
import expression.types.*;

import java.math.BigInteger;

public class CheckedParser<T extends MyNumber<T>> {

    enum Token {
        NUM, VARIABLE, PLUS, MINUS, MUL, DIV, OPEN_BRACKET, CLOSE_BRACKET, ABS, SQRT, POW, LOG, MOD, SQUARE
    }

    private String expression;
    private Token currentToken;
    private T value;
    private char variable;
    private int pos;
    private int bracketsBalance;
    private String dataType;

    private void parseNumber() throws ParserException {
        String sValue = "";
        if (dataType.equals("i") || dataType.equals("bi") || dataType.equals("u") || dataType.equals("b")) {
            while (pos < expression.length() && Character.isDigit(expression.charAt(pos))) {
                sValue += expression.charAt(pos++);
            }
            value = value.parse(sValue);
        } else if (dataType.equals("d") || dataType.equals("f")) {
            while (pos < expression.length() && (Character.isDigit(expression.charAt(pos)) || expression.charAt(pos) == '.')) {
                sValue += expression.charAt(pos++);
            }
            value = value.parse(sValue);
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
        // Num
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
                // Plus
                case '+':
                    currentToken = Token.PLUS;
                    break;
                //
                case '-':
                    currentToken = Token.MINUS;
                    break;
                //
                case '*':
                    if (expression.substring(pos, pos + 2).equals("**")) {
                        currentToken = Token.POW;
                        pos++;
                    } else {
                        currentToken = Token.MUL;
                    }
                    break;
                //
                case '/':
                    if (expression.substring(pos, pos + 2).equals("//")) {
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
                    if (expression.substring(pos, pos + 3).equals("abs")) {
                        currentToken = Token.ABS;
                        pos += 2;
                    }
                    break;
                // sqrt
                case 's':
                    if (expression.substring(pos, pos + 4).equals("sqrt")) {
                        currentToken = Token.SQRT;
                        pos += 3;
                    } else if (expression.substring(pos, pos + 6).equals("square")) {
                        currentToken = Token.SQUARE;
                        pos += 5;
                    }
                    break;
                case 'm':
                    if (expression.substring(pos, pos + 3).equals("mod")) {
                        currentToken = Token.MOD;
                        pos += 2;
                    }
                    break;
                default:
                    throw new ParserException("Undefined symbol: " + symbol);
            }
        }
        //System.out.println(currentToken);
        pos++;
    }

    private TripleExpression<T> parseMultiplier() throws ParserException {
        switch (currentToken) {
            case MINUS:
                nextToken();
                TripleExpression<T> num = parseMultiplier();
                return new CheckedNegate<>(num);
            case NUM:
                T number = value;
                nextToken();
                return new Const<>(number);
            case VARIABLE:
                String name = String.valueOf(variable);
                nextToken();
                return new Variable<>(name);
            case OPEN_BRACKET:
                nextToken();
                TripleExpression<T> answer = parseAddSub();
                nextToken();
                return answer;
            case ABS:
                nextToken();
                return new CheckedAbs<>(parseMultiplier());
            case SQRT:
                nextToken();
                return new CheckedSqrt<>(parseMultiplier());
            case SQUARE:
                nextToken();
                return new CheckedSquare<>(parseMultiplier());
        }
        throw new ParserException("Undefined token!");
    }

    private TripleExpression<T> parseSummand() throws ParserException {
        TripleExpression<T> answer = parseMultiplier();
        while (currentToken == Token.MUL || currentToken == Token.DIV || currentToken == Token.POW || currentToken == Token.LOG || currentToken == Token.MOD) {
            Token token = currentToken;
            nextToken();
            if (token == Token.MUL) {
                answer = new CheckedMultiply<>(answer, parseMultiplier());
            } else if (token == Token.DIV) {
                answer = new CheckedDivide<>(answer, parseMultiplier());
            } else if (token == Token.POW) {
                answer = new CheckedPower<>(answer, parseMultiplier());
            } else if (token == Token.LOG) {
                answer = new CheckedLogarithm<>(answer, parseMultiplier());
            } else if (token == Token.MOD) {
                answer = new CheckedMod<>(answer, parseMultiplier());
            }
        }
        return answer;
    }

    private TripleExpression<T> parseAddSub() throws ParserException {
        TripleExpression<T> answer = parseSummand();
        while (currentToken == Token.PLUS || currentToken == Token.MINUS) {
            Token token = currentToken;
            nextToken();
            if (token == Token.PLUS) {
                answer = new CheckedAdd<>(answer, parseSummand());
            } else if (token == Token.MINUS) {
                answer = new CheckedSubtract<>(answer, parseSummand());
            }
        }
        return answer;
    }

    /*
    public static void test(String expression, int x, int y, int z) {
        CheckedParser parser = new CheckedParser();
        try {
            TripleExpression<T> result = parser.parse(expression);
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
    */

    public TripleExpression<T> parse(String type, String s) throws ParserException {
        expression = s;
        pos = 0;
        bracketsBalance = 0;
        dataType = type;
        value = buildValueInstance(type);
        nextToken();
        TripleExpression<T> exp = parseAddSub();
        if (pos != expression.length() || bracketsBalance != 0) {
            throw new ParserException("Parse error!");
        }
        return exp;
    }

    private <T extends MyNumber> T buildValueInstance(String mode) {
        switch (mode) {
            case "i":
                return (T)new MyInt(0);
            case "bi":
                return (T)new MyBigInteger(BigInteger.ZERO);
            case "b":
                return (T)new MyByte((byte) 0);
            case "u":
                return (T)new MyUncheckedInt(0);
            case "d":
                return (T)new MyDouble(.0);
            case "f":
                return (T)new MyFloat((float) .0);
            default:
                return null;
        }
    }
}
