package expression;

import expression.exceptions.IncorrectOperationException;
import expression.types.MyNumber;

public class CheckedSqrt<T extends MyNumber<T>> extends UnaryOperation<T> {
    public CheckedSqrt(TripleExpression<T> a) {
        super(a);
    }

    public T operation(T x) throws IncorrectOperationException {
        return x.sqrt();
    }
}
