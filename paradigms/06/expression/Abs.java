package expression;

public class Abs extends UnaryOperation {
    public Abs(TripleExpression a) {
        super(a);
    }

    public int operation(int x) {
        return Math.abs(x);
    }
}