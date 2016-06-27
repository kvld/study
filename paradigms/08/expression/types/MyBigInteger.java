package expression.types;

import expression.exceptions.DBZException;
import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;

import java.math.BigInteger;

public class MyBigInteger extends MyNumber<MyBigInteger> {
    private BigInteger value;

    public MyBigInteger(BigInteger number) {
        this.value = number;
    }

    public BigInteger getValue() {
        return this.value;
    }

    public MyBigInteger abs() {
        return new MyBigInteger(value.abs());
    }

    public MyBigInteger add(MyBigInteger b) {
        return new MyBigInteger(value.add(b.getValue()));
    }


    public MyBigInteger div(MyBigInteger b) throws DBZException {
        if (b.getValue().equals(BigInteger.ZERO)) {
            throw new DBZException("Division by zero in MyBigInteger!");
        }
        return new MyBigInteger(value.divide(b.getValue()));
    }

    public MyBigInteger log(MyBigInteger b) throws IncorrectOperationException {
        if (value.compareTo(BigInteger.ZERO) <= 0) {
            throw new IncorrectOperationException("Log value should > 0!");
        }
        if (b.getValue().compareTo(BigInteger.ONE) <= 0) {
            throw new IncorrectOperationException("Log base should be > 1!");
        }
        if (value.compareTo(BigInteger.ONE) == 0) {
            return new MyBigInteger(BigInteger.ZERO);
        }
        BigInteger x = BigInteger.ONE, y = BigInteger.ZERO;
        while (x.compareTo(value) != 0) {
            if (x.compareTo(value) == -1 && value.compareTo(x.multiply(b.getValue())) == -1) {
                return new MyBigInteger(y);
            }
            y = y.add(BigInteger.ONE);
            x = x.multiply(b.getValue());
        }
        return new MyBigInteger(y);
    }


    public MyBigInteger mul(MyBigInteger b) {
        return new MyBigInteger(value.multiply(b.getValue()));
    }

    public MyBigInteger negate() {
        return new MyBigInteger(value.negate());
    }

    public MyBigInteger pow(MyBigInteger b) throws IncorrectOperationException, OverflowException {
        if (value.compareTo(BigInteger.ZERO) == 0 && b.getValue().compareTo(BigInteger.ZERO) == 0) {
            throw new IncorrectOperationException("0^0 is incorrect operation!");
        }
        if (b.getValue().compareTo(BigInteger.ZERO) == -1) {
            throw new IncorrectOperationException("Power should be > 0!");
        }
        return new MyBigInteger(value.pow((int) b.getValue().longValue()));
    }

    public MyBigInteger sqrt() throws IncorrectOperationException {
        if (value.compareTo(BigInteger.ZERO) == -1) {
            throw new IncorrectOperationException("Cannot get square root of negative number!");
        }
        BigInteger answer = BigInteger.ZERO;
        BigInteger l = BigInteger.ZERO, r = value;
        while (r.subtract(l).compareTo(BigInteger.ONE) == 1) {
            BigInteger mid = r.add(l).divide(BigInteger.ONE.add(BigInteger.ONE));
            if (mid.multiply(mid).compareTo(value) <= 0) {
                l = mid;
            }
            else {
                r = mid;
            }
        }
        for (BigInteger i = l; i.compareTo(r) == -1; i = i.add(BigInteger.ONE)) {
            if (i.multiply(i).compareTo(value) <= 0 && i.add(BigInteger.ONE).multiply(i.add(BigInteger.ONE)).compareTo(value) == 1) {
                answer = i;
                break;
            }
        }
        return (value.compareTo(BigInteger.ONE) == 0 ? new MyBigInteger(BigInteger.ONE) : new MyBigInteger(answer));
    }

    public MyBigInteger sub(MyBigInteger b) throws OverflowException {
        return new MyBigInteger(value.subtract(b.getValue()));
    }

    public MyBigInteger square() throws OverflowException {
        MyBigInteger copy = this;
        return copy.mul(this);
    }

    public MyBigInteger mod(MyBigInteger b) throws DBZException {
        if (b.getValue().equals(BigInteger.ZERO)) {
            throw new DBZException("Division by zero in MyBigInteger!");
        } else if (value.compareTo(BigInteger.ZERO) == -1 && b.getValue().compareTo(BigInteger.ZERO) == -1) {
            MyBigInteger res = new MyBigInteger(value.multiply(new BigInteger("-1")).mod(b.getValue().multiply(new BigInteger("-1"))));
            return res.mul(new MyBigInteger(new BigInteger("-1")));
        } else if (value.compareTo(BigInteger.ZERO) == -1 && b.getValue().compareTo(BigInteger.ZERO) == 1) {
            MyBigInteger res = new MyBigInteger(value.multiply(new BigInteger("-1")).mod(b.getValue()));
            return res.mul(new MyBigInteger(new BigInteger("-1")));
        } else if (value.compareTo(BigInteger.ZERO) == 1 && b.getValue().compareTo(BigInteger.ZERO) == -1) {
            MyBigInteger res = new MyBigInteger(value.mod(b.getValue().multiply(new BigInteger("-1"))));
            return res;
        }
        else if (value.compareTo(BigInteger.ZERO) == 0) {
            return new MyBigInteger(BigInteger.ZERO);
        }
        return new MyBigInteger(value.mod(b.getValue()));
    }

    public MyBigInteger parse(String s) {
        return new MyBigInteger(new BigInteger(s));
    }
}
