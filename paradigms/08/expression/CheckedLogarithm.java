package expression;

import expression.exceptions.IncorrectOperationException;
import expression.types.MyNumber;

public class CheckedLogarithm<T extends MyNumber<T>> extends BinaryOperation<T> {
    public CheckedLogarithm(TripleExpression<T> a, TripleExpression<T> b) {
        super(a, b);
    }

    public T operation(T a, T b) throws IncorrectOperationException {
        return a.log(b);
    }
}
