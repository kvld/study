package expression.types;

import expression.exceptions.DBZException;
import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;

/**
 * Created by vladislav on 14.04.15.
 */
public class MyUncheckedInt extends MyNumber<MyUncheckedInt> {

    protected Integer value;

    public MyUncheckedInt(Integer number) {
        this.value = number;
    }

    public Integer getValue() {
        return this.value;
    }

    public MyUncheckedInt abs() {
        return new MyUncheckedInt(value < 0 ? -value : value);
    }
    
    public MyUncheckedInt add(MyUncheckedInt b) {
        return new MyUncheckedInt(value + b.getValue());
    }


    public MyUncheckedInt div(MyUncheckedInt b) throws DBZException {
        if (b.getValue() == 0) {
            throw new DBZException("Division by zero in MyInteger!");
        }
        return new MyUncheckedInt(value / b.getValue());
    }

    public MyUncheckedInt log(MyUncheckedInt b) throws IncorrectOperationException {
        if (value <= 0) {
            throw new IncorrectOperationException("Log value should > 0!");
        }
        if (b.getValue() <= 1) {
            throw new IncorrectOperationException("Log base should be > 1!");
        }
        if (value == 1) {
            return new MyUncheckedInt(0);
        }
        int x = 1, y = 0;
        while (x != value) {
            if (x < value && x * b.getValue() > value) {
                return new MyUncheckedInt(y);
            }
            y++;
            if (((x * b.getValue()) / b.getValue() != x)) {
                return new MyUncheckedInt(y - 1);
            }
            x *= b.getValue();
        }
        return new MyUncheckedInt(y);
    }


    public MyUncheckedInt mul(MyUncheckedInt b) {
        return new MyUncheckedInt(value * b.getValue());
    }

    public MyUncheckedInt negate() {
        return new MyUncheckedInt(-value);
    }

    public MyUncheckedInt pow(MyUncheckedInt b) throws IncorrectOperationException {
        if (value == 0 && b.getValue() == 0) {
            throw new IncorrectOperationException("0^0 is incorrect operation!");
        }
        if (b.getValue() < 0) {
            throw new IncorrectOperationException("Power should be > 0!");
        }
        return new MyUncheckedInt(binaryPower(value, b.getValue()));
    }

    public int binaryPower(int a, int b) {
        if (b == 0) {
            return 1;
        } else if (a == 0) {
            return 0;
        } else {
            if (b % 2 == 1) {
                return binaryPower(a, b - 1) * a;
            } else {
                int c = binaryPower(a, b / 2);
                return c * c;
            }
        }
    }

    public MyUncheckedInt sqrt() throws IncorrectOperationException {
        if (value < 0) {
            throw new IncorrectOperationException("Cannot get square root of negative number!");
        }
        int answer = 0;
        int l = 0, r = value;
        while (r - l > 1) {
            int mid = (r + l) / 2;
            if ((mid * mid) / mid != mid) {
                // overflow
                r = mid;
            } else if (mid * mid <= value) {
                l = mid;
            }
            else {
                r = mid;
            }
        }
        for (int i = l; i < r; i++) {
            if (i * i <= value && (i + 1) * (i + 1) > value) {
                answer = i;
                break;
            }
        }
        return (value == 1 ? new MyUncheckedInt(1) : new MyUncheckedInt(answer));
    }

    public MyUncheckedInt sub(MyUncheckedInt b) {
        return new MyUncheckedInt(value - b.getValue());
    }

    public MyUncheckedInt mod(MyUncheckedInt b) throws DBZException {
        if (b.getValue() == 0) {
            throw new DBZException("Division by zero in MyCheckedInt!");
        }
        return new MyUncheckedInt(value % b.getValue());
    }

    public MyUncheckedInt square() throws OverflowException {
        MyUncheckedInt copy = this;
        return copy.mul(this);
    }

    public MyUncheckedInt parse(String s) {
        Integer parsedInt = Integer.parseUnsignedInt(s);
        // overflow
        if (parsedInt < 0) {
            return new MyUncheckedInt(Integer.MAX_VALUE);
        } else {
            return new MyUncheckedInt(parsedInt);
        }
    }
}