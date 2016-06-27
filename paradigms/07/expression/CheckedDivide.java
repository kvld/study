package expression;

import expression.exceptions.DBZException;
import expression.exceptions.OverflowException;

public class CheckedDivide extends BinaryOperation {
    public CheckedDivide(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) throws DBZException, OverflowException {
        if (b == 0) {
            throw new DBZException("Division by zero!");
        }
        if (b == -1 && a == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in divide: " + a + "/" + b);
        }
        return a / b;
    }
}
