package expression.exceptions;

public class DBZException extends ArithmeticErrorException {
    public DBZException(String exceptionMessage) {
        super(exceptionMessage);
    }
}
