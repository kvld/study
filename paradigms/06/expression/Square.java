package expression;

public class Square extends UnaryOperation {
    public Square(TripleExpression a) {
        super(a);
    }

    public int operation(int x) {
        return x * x;
    }
}