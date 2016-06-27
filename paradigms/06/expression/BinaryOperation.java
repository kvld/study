package expression;

public abstract class BinaryOperation implements TripleExpression {
    protected TripleExpression a, b;

    public BinaryOperation(TripleExpression a, TripleExpression b) {
        this.a = a;
        this.b = b;
    }

    public int evaluate(int x, int y, int z) {
        return operation(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }

    protected abstract int operation(int a, int b);
}
