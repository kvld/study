package expression;

public class Subtract extends BinaryOperation {
    public Subtract(Expression a, Expression b) {
        super(a, b);
    }

    public int operation(int a, int b) {
        return a - b;
    }
}
