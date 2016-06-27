package expression;

import expression.exceptions.IncorrectOperationException;

public class CheckedLogarithm extends BinaryOperation {
    public CheckedLogarithm(TripleExpression a, TripleExpression b) {
        super(a, b);
    }

    public int operation(int a, int b) throws IncorrectOperationException {
        if (a <= 0) {
            throw new IncorrectOperationException("Log value should > 0!");
        }
        if (b <= 1) {
            throw new IncorrectOperationException("Log base should be > 1!");
        }
        if (a == 1) {
            return 0;
        }
        int x = 1, y = 0;
        while (x != a) {
            if (x < a && x * b > a) {
                return y;
            }
            y++;
            if (((x * b) / b != x)) {
                return y - 1;
            }
            x *= b;
        }
        return y;
    }
}
