package expression.types;

import expression.exceptions.DBZException;
import expression.exceptions.IncorrectOperationException;

public class MyFloat extends MyNumber<MyFloat> {
    private Float value;

    public MyFloat(Float number) {
        this.value = number;
    }

    public Float getValue() {
        return this.value;
    }

    public MyFloat abs() {
        return new MyFloat(value < 0.0F ? 0.0F - value : value);
    }


    public MyFloat add(MyFloat b) {
        return new MyFloat(value + b.getValue());
    }


    public MyFloat div(MyFloat b) {
        return new MyFloat(value / b.getValue());
    }

    public MyFloat log(MyFloat b) throws IncorrectOperationException {
        if (value <= 0.0F) {
            throw new IncorrectOperationException("Log value should > 0!");
        }
        if (b.getValue() <= 1.0F) {
            throw new IncorrectOperationException("Log base should be > 1!");
        }
        if (value == 1.0) {
            return new MyFloat(0.0F);
        }
        return new MyFloat((float)(Math.log(value) / Math.log(b.getValue())));
    }


    public MyFloat mul(MyFloat b) {
        return new MyFloat(value * b.getValue());
    }

    public MyFloat negate() {
        return new MyFloat(-value);
    }

    public MyFloat pow(MyFloat b) throws IncorrectOperationException {
        if (value == 0.0F && b.getValue() == 0) {
            throw new IncorrectOperationException("0^0 is incorrect operation!");
        }
        if (b.getValue() < 0.0F) {
            throw new IncorrectOperationException("Power should be > 0!");
        }
        return new MyFloat((float)Math.pow(value, b.getValue()));
    }

    public MyFloat sqrt() throws IncorrectOperationException {
        if (value < 0.0F) {
            throw new IncorrectOperationException("Cannot get square root of negative number!");
        }
        return new MyFloat((float)Math.sqrt(value));
    }

    public MyFloat sub(MyFloat b) {
        return new MyFloat(value - b.getValue());
    }

    public MyFloat square() {
        MyFloat copy = this;
        return copy.mul(this);
    }

    public MyFloat mod(MyFloat b) throws DBZException {
        return new MyFloat(value % b.getValue());
    }

    public MyFloat parse(String s) {
        return new MyFloat(Float.parseFloat(s));
    }
}
