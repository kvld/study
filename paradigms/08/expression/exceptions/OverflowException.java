package expression.exceptions;

/**
 * Created by vladislav on 30.03.15.
 */
public class OverflowException extends ArithmeticErrorException {
    public OverflowException(String exceptionMessage) {
        super(exceptionMessage);
    }
}
