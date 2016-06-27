package expression;

import expression.exceptions.ArithmeticErrorException;

public abstract class UnaryOperation implements TripleExpression {
    protected TripleExpression a;

    public UnaryOperation(TripleExpression a) {
        this.a = a;
    }

    public int evaluate(int x, int y, int z) throws ArithmeticErrorException {
        return operation(a.evaluate(x, y, z));
    }

    protected abstract int operation(int a) throws ArithmeticErrorException;
}
