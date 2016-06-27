package expression;

import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedNegate<T extends MyNumber<T>> extends UnaryOperation<T> {
    public CheckedNegate(TripleExpression<T> a) {
        super(a);
    }

    public T operation(T x) throws OverflowException {
        return x.negate();
    }
}