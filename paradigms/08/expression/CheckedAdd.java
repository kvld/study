package expression;

import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedAdd<T extends MyNumber<T>> extends BinaryOperation<T> {
    public CheckedAdd(TripleExpression<T> a, TripleExpression<T> b) {
        super(a, b);
    }

    public T operation(T a, T b) throws OverflowException {
        return a.add(b);

    }
}
