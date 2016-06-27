package expression;

public class UnaryMinus extends UnaryOperation {
    public UnaryMinus(TripleExpression a) {
        super(a);
    }

    public int operation(int x) {
        return -x;
    }
}