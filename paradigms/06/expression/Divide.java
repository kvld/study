package expression;

public class Divide extends BinaryOperation {
    public Divide(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a / b;
    }
}
