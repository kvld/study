package expression;

import expression.exceptions.IncorrectOperationException;

public class CheckedSqrt extends UnaryOperation {
    public CheckedSqrt(TripleExpression a) {
        super(a);
    }

    @Override
    public int operation(int x) throws IncorrectOperationException {
        if (x < 0) {
            throw new IncorrectOperationException("Cannot get square root of negative number!");
        }
        int answer = 0;
        int l = 0, r = x;
        while (r - l > 1) {
            int mid = (r + l) / 2;
            if ((mid * mid) / mid != mid) {
                // overflow
                r = mid;
            } else if (mid * mid <= x) {
                l = mid;
            }
            else {
                r = mid;
            }
        }
        for (int i = l; i < r; i++) {
            if (i * i <= x && (i + 1) * (i + 1) > x) {
                answer = i;
                break;
            }
        }
        return (x == 1 ? 1 : answer);
    }
}
