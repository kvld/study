package expression;

import expression.exceptions.OverflowException;

public class CheckedAdd extends BinaryOperation {
    public CheckedAdd(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) throws OverflowException {
        if (a > 0 && b > 0 && (Integer.MAX_VALUE - a < b) || a < 0 && b < 0 && (Integer.MIN_VALUE - a > b)) {
            throw new OverflowException("Overflow exception in add: " + a + "+" + b);
        }
        return a + b;
    }
}
