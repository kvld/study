package expression;

import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedPower<T extends MyNumber<T>> extends BinaryOperation<T> {
    public CheckedPower(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public T operation(T a, T b) throws IncorrectOperationException, OverflowException {
        return a.pow(b);
    }
}
