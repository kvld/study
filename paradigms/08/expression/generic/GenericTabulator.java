package expression.generic;

import expression.*;
import expression.types.*;

import java.math.BigInteger;

public class GenericTabulator implements Tabulator {

    private Object evaluate(int x, int y, int z, String mode, TripleExpression parsedExpression) {
        try {
            switch (mode) {
                case "i":
                    return ((MyInt)parsedExpression.evaluate(new MyInt(x), new MyInt(y), new MyInt(z))).getValue();
                case "d":
                    return ((MyDouble)parsedExpression.evaluate(new MyDouble((double) x), new MyDouble((double) y), new MyDouble((double) z))).getValue();
                case "bi":
                    return ((MyBigInteger)parsedExpression.evaluate(new MyBigInteger(new BigInteger(String.valueOf(x))), new MyBigInteger(new BigInteger(String.valueOf(y))), new MyBigInteger(new BigInteger(String.valueOf(z))))).getValue();
                case "f":
                    return ((MyFloat)parsedExpression.evaluate(new MyFloat((float) x), new MyFloat((float) y), new MyFloat((float) z))).getValue();
                case "u":
                    return ((MyUncheckedInt)parsedExpression.evaluate(new MyUncheckedInt(x), new MyUncheckedInt(y), new MyUncheckedInt(z))).getValue();
                case "b":
                    return ((MyByte)parsedExpression.evaluate(new MyByte((byte) x), new MyByte((byte) y), new MyByte((byte) z))).getValue();
            }
        } catch (Exception e) {
            return null;
        }
        return null;
    }

    public Object[][][] tabulate(String mode, String expression, int x1, int x2, int y1, int y2, int z1, int z2) throws Exception {
        Object[][][] result = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        CheckedParser<? extends MyNumber> parser = new CheckedParser<>();
        TripleExpression parsedExpression = parser.parse(mode, expression);
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                for (int z = z1; z <= z2; z++) {
                    result[x - x1][y - y1][z - z1] = evaluate(x, y, z, mode, parsedExpression);
                }
            }
        }
        return result;
    }
}
