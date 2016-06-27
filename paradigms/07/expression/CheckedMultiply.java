package expression;

import expression.exceptions.ArithmeticErrorException;
import expression.exceptions.OverflowException;

public class CheckedMultiply extends BinaryOperation {
    public CheckedMultiply(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) throws ArithmeticErrorException {
        if (a != 0 && b != 0) {
            try {
                return Math.multiplyExact(a, b);
            } catch (ArithmeticException e) {
                throw new OverflowException("Overflow exception in mul: " + a + "*" + b);
            }
        } else {
            return 0;
        }
    }
}
