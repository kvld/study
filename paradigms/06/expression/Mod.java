package expression;

public class Mod extends BinaryOperation {
    public Mod(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a % b;
    }
}
