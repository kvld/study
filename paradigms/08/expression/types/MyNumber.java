package expression.types;

import expression.exceptions.DBZException;
import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;

/**
 * Created by vladislav on 06.04.15.
 */
public abstract class MyNumber<T> {
    public abstract T abs() throws OverflowException;
    public abstract T add(T b) throws OverflowException;
    public abstract T div(T b) throws DBZException, OverflowException;
    public abstract T log(T b) throws IncorrectOperationException;
    public abstract T mul(T b) throws OverflowException;
    public abstract T negate() throws OverflowException;
    public abstract T pow(T b) throws IncorrectOperationException, OverflowException;
    public abstract T sqrt() throws IncorrectOperationException;
    public abstract T sub(T b) throws OverflowException;

    public abstract T square() throws OverflowException;
    public abstract T mod(T b) throws DBZException;

    public abstract T parse(String s);
}
