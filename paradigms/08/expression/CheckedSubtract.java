package expression;

import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedSubtract<T extends MyNumber<T>> extends BinaryOperation<T> {
    public CheckedSubtract(TripleExpression<T> a, TripleExpression<T> b) {
        super(a, b);
    }

    public T operation(T a, T b) throws OverflowException {
        return a.sub(b);
    }
}
