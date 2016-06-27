package expression;

public class LeftShift extends BinaryOperation {
    public LeftShift(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a << b;
    }
}
