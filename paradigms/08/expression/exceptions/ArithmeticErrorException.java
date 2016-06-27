package expression.exceptions;

public class ArithmeticErrorException extends RuntimeException {
    public ArithmeticErrorException(String exceptionMessage) {
        super(exceptionMessage);
    }
}
