package expression;

public abstract class BinaryOperation implements Expression {
    protected Expression a, b;

    public BinaryOperation(Expression a, Expression b) {
        this.a = a;
        this.b = b;
    }

    public int evaluate(int x) {
        return operation(a.evaluate(x), b.evaluate(x));
    }

    public int evaluate(int x, int y, int z) {
        return operation(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }

    protected abstract int operation(int a, int b);
}
