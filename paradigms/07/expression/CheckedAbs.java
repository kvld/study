package expression;

import expression.exceptions.OverflowException;

public class CheckedAbs extends UnaryOperation {
    public CheckedAbs(TripleExpression a) {
        super(a);
    }

    public int operation(int x) throws OverflowException {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in abs: " + x);
        }
        return (x < 0 ? -x : x);
    }
}
