package expression;

public class ExpressionParser implements Parser {

    enum Token {
        Num, Variable, Plus, Minus, Mul, Div, OpenBracket, CloseBracket, Square, Abs, LeftShift, RightShift, Mod;
    }

    private String expression;
    private Token currentToken;
    private int value;
    private char variable;
    private int pos;

    
    private void parseNumber() {
        String sValue = "";
        while (pos < expression.length() && Character.isDigit(expression.charAt(pos))) {
            sValue += expression.charAt(pos++);
        }
        value = Integer.parseUnsignedInt(sValue);
    }

    private void nextToken() {
        while (pos < expression.length() && Character.isWhitespace(expression.charAt(pos))) {
            pos++;
        }
        if (pos >= expression.length()) {
            return;
        }

        char symbol = expression.charAt(pos);
        // Num
        if (Character.isDigit(symbol)) {
            currentToken = Token.Num;
            parseNumber();
            pos--;
        }
        switch (symbol) {
            // Var
            case 'x' :
            case 'y' :
            case 'z':
                currentToken = Token.Variable;
                variable = symbol;
                break;
            // Plus
            case '+' :
                currentToken = Token.Plus;
                break;
            //
            case '-' :
                currentToken = Token.Minus;
                break;
            //
            case '*' :
                currentToken = Token.Mul;
                break;
            //
            case '/' :
                currentToken = Token.Div;
                break;
            //
            case '(' :
                currentToken = Token.OpenBracket;
                break;
            //
            case ')' :
                currentToken = Token.CloseBracket;
                break;
            // abs
            case 'a' :
                if (expression.substring(pos, pos + 3).equals("abs")) {
                    currentToken = Token.Abs;
                    pos += 2;
                }
                break;
            // sqr
            case 's' :
                if (expression.substring(pos, pos + 6).equals("square")) {
                    currentToken = Token.Square;
                    pos += 5;
                }
                break;
            // mod
            case 'm' :
                if (expression.substring(pos, pos + 3).equals("mod")) {
                    currentToken = Token.Mod;
                    pos += 2;
                }
                break;
            // shl
            case '<' :
                if (expression.substring(pos, pos + 2).equals("<<")) {
                    currentToken = Token.LeftShift;
                    pos++;
                }
                break;
            // shr
            case '>' :
                if (expression.substring(pos, pos + 2).equals(">>")) {
                    currentToken = Token.RightShift;
                    pos++;
                }
                break;
        }
        //System.out.println(currentToken);
        pos++;
    }

    private TripleExpression parseMultiplier() {
        switch (currentToken) {
            case Minus :
                nextToken();
                return new UnaryMinus(parseMultiplier());
            case Num :
                int number = value;
                nextToken();
                return new Const(number);
            case Variable :
                String name = String.valueOf(variable);
                nextToken();
                return new Variable(name);
            case OpenBracket :
                nextToken();
                TripleExpression answer = parseShifts();
                nextToken();
                return answer;
            case Abs :
                nextToken();
                return new Abs(parseMultiplier());
            case Square :
                nextToken();
                return new Square(parseMultiplier());
            default :
                return null;
        }
    }

    private TripleExpression parseMulDivMod() {
        TripleExpression answer = parseMultiplier();
        while (currentToken == Token.Mul || currentToken == Token.Div || currentToken == Token.Mod) {
            Token token = currentToken;
            nextToken();
            if (token == Token.Mul) {
                answer = new Multiply(answer, parseMultiplier());
            } else if (token == Token.Div) {
                answer = new Divide(answer, parseMultiplier());
            } else if (token == Token.Mod) {
                answer = new Mod(answer, parseMultiplier());
            }
        }
        return answer;
    }

    private TripleExpression parseShifts() {
        TripleExpression answer = parseAddSub();
        while (currentToken == Token.LeftShift || currentToken == Token.RightShift) {
            Token token = currentToken;
            nextToken();
            if (token == Token.LeftShift) {
                answer = new LeftShift(answer, parseAddSub());
            } else if (token == Token.RightShift) {
                answer = new RightShift(answer, parseAddSub());
            }
        }
        return answer;
    }

    private TripleExpression parseAddSub() {
        TripleExpression answer = parseMulDivMod();
        while (currentToken == Token.Plus || currentToken == Token.Minus) {
            Token token = currentToken;
            nextToken();
            if (token == Token.Plus) {
                answer = new Add(answer, parseMulDivMod());
            } else if (token == Token.Minus) {
                answer = new Subtract(answer, parseMulDivMod());
            }
        }
        return answer;
    }

    public TripleExpression parse(String s) {
        expression = s;
        pos = 0;
        nextToken();
        return parseShifts();
    }
}
