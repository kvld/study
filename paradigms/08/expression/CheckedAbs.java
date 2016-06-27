package expression;

import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedAbs<T extends MyNumber<T>> extends UnaryOperation<T> {
    public CheckedAbs(TripleExpression<T> a) {
        super(a);
    }

    public T operation(T x) throws OverflowException {
        return x.abs();
    }
}
