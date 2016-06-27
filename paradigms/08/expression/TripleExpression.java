package expression;

import expression.types.MyNumber;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface TripleExpression<T extends MyNumber<T>> {
    T evaluate(T x, T y, T z);
}