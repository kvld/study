package expression;

import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedSquare<T extends MyNumber<T>> extends UnaryOperation<T> {
    public CheckedSquare(TripleExpression<T> a) {
        super(a);
    }

    public T operation(T x) throws OverflowException {
        return x.square();
    }
}
