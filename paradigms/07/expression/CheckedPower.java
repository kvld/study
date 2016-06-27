package expression;

import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;

public class CheckedPower extends BinaryOperation {
    public CheckedPower(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) throws IncorrectOperationException, OverflowException {
        if (a == 0 && b == 0) {
            throw new IncorrectOperationException("0^0 is incorrect operation!");
        }
        if (b < 0) {
            throw new IncorrectOperationException("Power should be > 0!");
        }
        if (b == 0) {
            return 1;
        }
        if (a == 0) {
            return 0;
        }
        if (b % 2 == 1) {
            return operation(a, b - 1) * a;
        } else {
            int c = operation(a, b / 2);
            if (((c * c) / c != c)) {
                throw new OverflowException("Overflow exception in power: " + a + "^" + b);
            }
            return c * c;
        }
    }
}
