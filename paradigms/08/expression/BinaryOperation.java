package expression;

import expression.exceptions.ArithmeticErrorException;
import expression.types.MyNumber;

public abstract class BinaryOperation<T extends MyNumber<T>> implements TripleExpression<T> {
    protected TripleExpression<T> a, b;

    public BinaryOperation(TripleExpression<T> a, TripleExpression<T> b) {
        this.a = a;
        this.b = b;
    }

    public T evaluate(T x, T y, T z) throws ArithmeticErrorException {
        return operation(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }

    protected abstract T operation(T a, T b) throws ArithmeticErrorException;
}
