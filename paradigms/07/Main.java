import expression.*;

public class Main {
    public static void main(String[] args) {
        /*
        try {
            int a = new CheckedSubtract(new VARIABLE("x"), new VARIABLE("y")).evaluate(0, Integer.MIN_VALUE, 0);
            //int a = new CheckedNegate(new VARIABLE("x")).evaluate(Integer.MIN_VALUE, 0, 0);
            System.out.println(a);
        } catch (ArithmeticErrorException e) {
            System.out.println(e.getMessage());
        }*/
        CheckedParser.test(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]));
    }
}
