package expression;

public class Divide extends BinaryOperation {
    public Divide(Expression a, Expression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a / b;
    }
}
