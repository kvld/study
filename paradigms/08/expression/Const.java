package expression;

import expression.types.MyNumber;

public class Const<T extends MyNumber<T>> implements TripleExpression<T> {
    private final T value;

    public Const(T value) {
        this.value = value;
    }

    public T evaluate(T x, T y, T z) {
        return value;
    }
}