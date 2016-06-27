package expression;

public class Multiply extends BinaryOperation {
    public Multiply(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a * b;
    }
}
