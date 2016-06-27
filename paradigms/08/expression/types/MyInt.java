package expression.types;

import expression.exceptions.OverflowException;

/**
 * Created by vladislav on 20.04.15.
 */
public class MyInt extends MyNumber<MyInt> {
    private MyUncheckedInt value;

    public MyInt(Integer number) {
        value = new MyUncheckedInt(number);
    }

    public Integer getValue() {
        return value.getValue();
    }

    public static MyInt cast(MyUncheckedInt a) {
        return new MyInt(a.getValue());
    }

    public static MyUncheckedInt cast(MyInt a) {
        return new MyUncheckedInt(a.getValue());
    }

    public MyInt abs() throws OverflowException {
        if (value.getValue() == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in MyInt.abs: " + value.getValue());
        }
        return cast(value.abs());
    }

    public MyInt add(MyInt b) throws OverflowException {
        if (value.getValue() > 0 && b.getValue() > 0 && (Integer.MAX_VALUE - value.getValue() < b.getValue()) || value.getValue() < 0 && b.getValue() < 0 && (Integer.MIN_VALUE - value.getValue() > b.getValue())) {
            throw new OverflowException("Overflow exception in MyInt.add: " + value.getValue() + "+" + b);
        }
        return cast(value.add(cast(b)));
    }

    public MyInt div(MyInt b) throws OverflowException {
        if (b.getValue() == -1 && value.getValue() == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in MyInt.divide: " + value.getValue() + "/" + b.getValue());
        }
        return cast(value.div(cast(b)));
    }

    public MyInt log(MyInt b) {
        return cast(value.log(cast(b)));
    }

    public MyInt mul(MyInt b) throws OverflowException {
        if (value.getValue() != 0 && b.getValue() != 0) {
            if (((value.getValue() * b.getValue()) / b.getValue() != value.getValue())) {
                throw new OverflowException("Overflow exception in MyInt.mul: " + value.getValue() + "*" + b.getValue());
            } else if ((value.getValue() == Integer.MIN_VALUE && b.getValue() < 0) || (b.getValue() == Integer.MIN_VALUE && value.getValue() < 0)) {
                throw new OverflowException("Overflow exception in MyInt.mul: " + value.getValue() + "*" + b.getValue());
            } else {
                return cast(value.mul(cast(b)));
            }
        } else {
            return new MyInt(0);
        }
    }

    public MyInt negate() throws OverflowException {
        if (value.getValue() == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in MyInt.negate: " + value.getValue());
        }
        return cast(value.negate());
    }

    public MyInt pow(MyInt b) throws OverflowException {
        return new MyInt(binaryPower(value.getValue(), b.getValue()));
    }

    public int binaryPower(int a, int b) throws OverflowException {
        if (b == 0) {
            return 1;
        } else if (a == 0) {
            return 0;
        } else {
            if (b % 2 == 1) {
                return binaryPower(a, b - 1) * a;
            } else {
                int c = binaryPower(a, b / 2);
                if (((c * c) / c != c)) {
                    throw new OverflowException("Overflow exception in MyInt.power: " + a + "^" + b);
                }
                return c * c;
            }
        }
    }

    public MyInt sqrt() {
        return cast(value.sqrt());
    }

    public MyInt sub(MyInt b) throws OverflowException {
        if (value.getValue() > 0 && b.getValue() < 0 && (Integer.MAX_VALUE - value.getValue() < -b.getValue()) || value.getValue() < 0 && b.getValue() > 0 && (Integer.MIN_VALUE - value.getValue() > -b.getValue())) {
            throw new OverflowException("Overflow exception in sub!");
        } else if (value.getValue() >= 0 && b.getValue() == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow exception in sub!");
        }
        return cast(value.sub(cast(b)));
    }

    public MyInt mod(MyInt b) {
        return cast(value.mod(cast(b)));
    }

    public MyInt square() {
        return cast(value.square());
    }

    public MyInt parse(String s) {
        return cast(value.parse(s));
    }
}

