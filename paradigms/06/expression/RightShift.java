package expression;

public class RightShift extends BinaryOperation {
    public RightShift(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a >> b;
    }
}
