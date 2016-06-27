package expression;

import expression.exceptions.OverflowException;

public class CheckedSubtract extends BinaryOperation {
    public CheckedSubtract(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) throws OverflowException {
        if (a > 0 && b < 0 && (Integer.MAX_VALUE - a < -b) || a < 0 && b > 0 && (Integer.MIN_VALUE - a > -b)) {
            throw new OverflowException("Overflow exception in sub!");
        } else if (a >= 0 && b == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in sub!");
        }
        return a - b;
    }
}
