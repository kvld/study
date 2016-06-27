package expression;

import expression.exceptions.ArithmeticErrorException;
import expression.types.MyNumber;

public abstract class UnaryOperation<T extends MyNumber<T>> implements TripleExpression<T> {
    protected TripleExpression<T> a;

    public UnaryOperation(TripleExpression a) {
        this.a = a;
    }

    public T evaluate(T x, T y, T z) throws ArithmeticErrorException {
        return operation(a.evaluate(x, y, z));
    }

    protected abstract T operation(T a) throws ArithmeticErrorException;
}
