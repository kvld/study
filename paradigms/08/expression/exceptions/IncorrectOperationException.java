package expression.exceptions;

/**
 * Created by vladislav on 31.03.15.
 */
public class IncorrectOperationException extends ArithmeticErrorException {
    public IncorrectOperationException(String message) {
        super(message);
    }
}
