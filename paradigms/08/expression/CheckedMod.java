package expression;

import expression.exceptions.DBZException;
import expression.exceptions.OverflowException;
import expression.types.MyNumber;

public class CheckedMod<T extends MyNumber<T>> extends BinaryOperation<T> {
    public CheckedMod(TripleExpression<T> a, TripleExpression<T> b) {
        super(a, b);
    }

    public T operation(T a, T b) throws DBZException, OverflowException {
        return a.mod(b);
    }
}
