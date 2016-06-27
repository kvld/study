package expression;

import expression.exceptions.OverflowException;

public class CheckedNegate extends UnaryOperation {
    public CheckedNegate(TripleExpression a) {
        super(a);
    }

    public int operation(int x) throws OverflowException {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in negate: " + x);
        }
        return -x;
    }
}