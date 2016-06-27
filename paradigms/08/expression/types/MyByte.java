package expression.types;

import expression.exceptions.DBZException;
import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;

public class MyByte extends MyNumber<MyByte> {
    private Byte value;

    public MyByte(Byte number) {
        this.value = number;
    }

    public Byte getValue() {
        return this.value;
    }

    public MyByte abs() {
        return new MyByte(value < 0 ? (byte)-value : value);
    }


    public MyByte add(MyByte b) {
        return new MyByte((byte)(value + b.getValue()));
    }


    public MyByte div(MyByte b) throws DBZException {
        if (b.getValue() == 0) {
            throw new DBZException("Division by zero in MyInteger!");
        }
        return new MyByte((byte)(value / b.getValue()));
    }

    public MyByte log(MyByte b) throws IncorrectOperationException {
        if (b.getValue() <= 1) {
            throw new IncorrectOperationException("Log base should be > 1!");
        }
        if (value == 1) {
            return new MyByte((byte)0);
        }
        int x = 1, y = 0;
        while (x != value) {
            if (x < value && x * b.getValue() > value) {
                return new MyByte((byte)y);
            }
            y++;
            if (((x * b.getValue()) / b.getValue() != x)) {
                return new MyByte((byte)(y - 1));
            }
            x *= b.getValue();
        }
        return new MyByte((byte)y);
    }


    public MyByte mul(MyByte b) {
        if (value != 0 && b.getValue() != 0) {
            return new MyByte((byte)(value * b.getValue()));
        } else {
            return new MyByte((byte)0);
        }
    }

    public MyByte negate() {
        return new MyByte((byte)-value);
    }

    public MyByte pow(MyByte b) throws IncorrectOperationException, OverflowException {
        if (value == 0 && b.getValue() == 0) {
            throw new IncorrectOperationException("0^0 is incorrect operation!");
        }
        return new MyByte(binaryPower(value, b.getValue()));
    }

    public Byte binaryPower(int a, int b) {
        if (b == 0) {
            return 1;
        } else if (a == 0) {
            return 0;
        } else {
            if (b % 2 == 1) {
                return (byte)(binaryPower(a, b - 1) * a);
            } else {
                int c = binaryPower(a, b / 2);
                return (byte)(c * c);
            }
        }
    }

    public MyByte sqrt() {
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
        return (value == 1 ? new MyByte((byte)1) : new MyByte((byte)answer));
    }

    public MyByte sub(MyByte b) {
        return new MyByte((byte)(value - b.getValue()));
    }

    public MyByte mod(MyByte b) throws DBZException {
        if (b.getValue() == 0) {
            throw new DBZException("Division by zero in MyIntWOOverflow!");
        }
        return new MyByte((byte)(value % b.getValue()));
    }

    public MyByte square() {
        MyByte copy = this;
        return copy.mul(this);
    }

    public MyByte parse(String s) {
        Byte parsedByte = Byte.parseByte(s);
        return new MyByte(parsedByte);
    }
}
