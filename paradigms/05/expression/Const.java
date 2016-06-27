package expression;

public class Const implements Expression {
    private final int value;

    public Const(int value) {
        this.value = value;
    }

    public int evaluate(int x) {
        return value;
    }

    public int evaluate(int x, int y, int z) {
        return value;
    }
}
