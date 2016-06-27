import expression.*;

public class Main {
    public static void main(String[] args) {
        ExpressionParser parser = new ExpressionParser();
        try {
            System.out.println(parser.parse("(1 + 2) << (3 * 4)").evaluate(0, 0, 0));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
