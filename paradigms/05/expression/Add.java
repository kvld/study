package expression;

public class Add extends BinaryOperation {
    public Add(Expression a, Expression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a + b;
    }
}
