package expression.types;

import expression.exceptions.DBZException;
import expression.exceptions.IncorrectOperationException;
import expression.exceptions.OverflowException;

public class MyDouble extends MyNumber<MyDouble> {
    private Double value;

    public MyDouble(Double number) {
        this.value = number;
    }

    public Double getValue() {
        return this.value;
    }

    public MyDouble abs() {
        return new MyDouble(value < 0.0 ? 0.0 - value : value);
    }


    public MyDouble add(MyDouble b) {
        return new MyDouble(value + b.getValue());
    }


    public MyDouble div(MyDouble b) {
        return new MyDouble(value / b.getValue());
    }

    public MyDouble log(MyDouble b) throws IncorrectOperationException {
        if (value <= 0.0) {
            throw new IncorrectOperationException("Log value should > 0!");
        }
        if (b.getValue() <= 1.0) {
            throw new IncorrectOperationException("Log base should be > 1!");
        }
        if (value == 1.0) {
            return new MyDouble(0.0);
        }
        return new MyDouble(Math.log(value) / Math.log(b.getValue()));
    }


    public MyDouble mul(MyDouble b) throws OverflowException {
        return new MyDouble(value * b.getValue());
    }

    public MyDouble negate() throws OverflowException {
        return new MyDouble(-value);
    }

    public MyDouble pow(MyDouble b) throws IncorrectOperationException, OverflowException {
        if (value == 0.0 && b.getValue() == 0) {
            throw new IncorrectOperationException("0^0 is incorrect operation!");
        }
        if (b.getValue() < 0.0) {
            throw new IncorrectOperationException("Power should be > 0!");
        }
        return new MyDouble(Math.pow(value, b.getValue()));
    }

    public MyDouble sqrt() throws IncorrectOperationException {
        if (value < 0) {
            throw new IncorrectOperationException("Cannot get square root of negative number!");
        }
        return new MyDouble(Math.sqrt(value));
    }

    public MyDouble sub(MyDouble b) throws OverflowException {
        return new MyDouble(value - b.getValue());
    }

    public MyDouble square() throws OverflowException {
        MyDouble copy = this;
        return copy.mul(this);
    }

    public MyDouble mod(MyDouble b) throws DBZException {
        return new MyDouble(value % b.getValue());
    }

    public MyDouble parse(String s) {
        return new MyDouble(Double.parseDouble(s));
    }
}
