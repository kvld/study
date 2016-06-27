package expression;

import expression.exceptions.ArithmeticErrorException;
import expression.types.MyNumber;

public class CheckedMultiply<T extends MyNumber<T>> extends BinaryOperation<T> {
    public CheckedMultiply(TripleExpression<T> a, TripleExpression<T> b) {
        super(a, b);
    }

    public T operation(T a, T b) throws ArithmeticErrorException {
        return a.mul(b);
    }
}
