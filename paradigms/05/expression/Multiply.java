package expression;

public class Multiply extends BinaryOperation {
    public Multiply(Expression a, Expression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a * b;
    }
}
