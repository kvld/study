#include "big_integer.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <cassert>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

const big_integer ZERO = big_integer(0);
const big_integer ONE = big_integer(1);

void big_integer::debug_print() {
    std::cerr << "== Debug print ==\n";
    std::cerr << "Sign: " << (sign == -1 ? "-" : (sign == 0 ? "0" : "+")) << std::endl;
    for (size_t i = 0; i < digits.size(); i++) {
        std::cerr << digits[i] << ' ';
    }
    std::cerr << std::endl;
}

inline void big_integer::__remove_leading_zeros() {
    while ((digits.size() > 1) && (digits[digits.size() - 1] == 0))
        digits.pop_back();
    if (digits.size() == 1 && digits[0] == 0)
        sign = 0;
}

void big_integer::__shift_digits(int shift) {
    digits.resize(digits.size() + shift);
    for (int i = digits.size() - 1; i >= shift; i--) {
        digits[i] = digits[i - shift];
    }
    for (size_t i = 0; i < shift; i++) {
        digits[i] = 0;
    }
}

inline void big_integer::__additional_code()
{
    for (size_t i = 0; i < digits.size(); i++) {
        digits[i] = (~digits[i]) + 1;
    }
}

/* Constructors */

big_integer::big_integer(big_integer const &other) {
    sign = other.sign;
    digits = other.digits;
}

big_integer::big_integer(int a) {
    digits.clear();
    if (a == 0) {
        sign = 0;
        digits.push_back(0);
        return;
    }
    sign = (a > 0 ? 1 : -1);
    digits.push_back((a < 0 ? -a : a));
}

big_integer::big_integer(long long a) {
    digits.clear();
    if (a == 0) {
        sign = 0;
        digits.push_back(0);
        return;
    }
    sign = (a > 0 ? 1 : -1);
    digits.push_back(a % BASE);
    digits.push_back(a / BASE);
}

big_integer::big_integer(uint a) {
    digits.clear();
    if (a == 0) {
        sign = 0;
        digits.push_back(0);
        return;
    }
    sign = 1;
    digits.push_back(a);
}


big_integer::big_integer() {
    *this = ZERO;
}

big_integer::big_integer(std::string const &str) {
    size_t pos = 0;
    big_integer c;
    bool negative = false;
    if (str[0] == '-') {
        negative = true;
        pos++;
    }
    if (pos == str.size()) {
        throw new std::runtime_error("Invalid input string!");
    }
    for (size_t i = pos; i < (int) str.size(); i++) {
        int cur = (str[i] - '0');
        c *= 10;
        c += cur;
    }
    c.sign = (negative ? -1 : 1);
    c.__remove_leading_zeros();
    *this = c;
}

/* Destructor */

big_integer::~big_integer() {
    sign = 0;
    digits.clear();
}

/* Operators =, +=, -=, *=, /=, %= */

big_integer &big_integer::operator=(big_integer const &other) {
    sign = other.sign;
    digits = other.digits;
    return *this;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    if (sign != rhs.sign) {
        // a += (-b) -> a = a - -b
        // a += b, a < 0 -> a = b - a
        if (rhs.sign < 0) {
            *this -= -rhs;
            return *this;
        } else {
            *this = rhs - -*this;
            return *this;
        }
    }

    digits.resize(MAX(digits.size(), rhs.digits.size()));
    int carry = 0;
    for (size_t i = 0; i < digits.size() || carry; i++) {
        if (i == digits.size()) {
            digits.push_back(0);
        }
        ull next_digit = (i < rhs.digits.size() ? rhs.digits[i] : 0);
        ull current = digits[i] + next_digit + carry;
        carry = current >= (ull)BASE;
        if (carry) {
            digits[i] = current - BASE;
        } else {
            digits[i] = current;
        }
    }
    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    // a -= (-b) -> a = a - -b = a + b
    if ((sign != rhs.sign) && (rhs.sign < 0)) {
        return *this = (*this + -rhs);
    }
    // a -= (-b), a < 0 -> a = b - a
    if (sign < 0 && rhs.sign < 0) {
        return *this = (-rhs - -*this);
    }
    // a -= b, a < 0 -> a = -(a + b)
    if (sign < 0 && rhs.sign > 0) {
        return *this = -(-*this + rhs);
    }
    // a -= b, b > a -> a = -(b - a)
    if (rhs > *this) {
        return *this = -(rhs - *this);
    }
    digits.resize(MAX(digits.size(), rhs.digits.size()));
    int carry = 0;
    for (size_t i = 0; i < rhs.digits.size() || carry; i++) {
        if (i == digits.size()) {
            digits.push_back(0);
        }
        ll tmp = (ll)digits[i] - (ll)(i < rhs.digits.size() ? rhs.digits[i] : 0) - carry;
        carry = (tmp < 0);
        if (carry) {
            digits[i] = tmp + BASE;
        } else {
            digits[i] = (uint)tmp;
        }
    }
    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    if (sign == 0 || rhs.sign == ZERO) {
        *this = ZERO;
        return *this;
    }
    if (rhs.digits.size() == 1 && rhs.digits[0] < INT32_MAX) {
        *this *= rhs.digits[0] * rhs.sign;
        return *this;
    }

    big_integer product = big_integer();
    product.sign = sign * rhs.sign;
    product.digits.resize(digits.size() + rhs.digits.size());
    for (size_t i = 0; i < digits.size(); i++) {
        uint carry = 0;
        for (size_t j = 0; j < rhs.digits.size() || carry; j++) {
            uint next_digit = 0;
            if (j < rhs.digits.size())
                next_digit = rhs.digits[j];
            ull cur = (ull)product.digits[i + j] + (ull)digits[i] * next_digit + carry;
            carry = cur / BASE;
            product.digits[i + j] = (uint)(cur - carry * (ull)BASE);
        }
    }
    *this = product;
    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator*=(int const &rhs) {
    if (rhs == 0) {
        return *this = ZERO;
    }

    sign = sign * ((rhs < 0) ? -1 : 1);

    int r = (rhs < 0 ? -rhs : rhs);
    ll carry = 0;
    for (size_t i = 0; i < digits.size() || carry; i++) {
        if (i == digits.size()) {
            digits.push_back(0);
        }
        ll cur = carry + digits[i] * 1LL * r;
        digits[i] = cur % BASE;
        carry = cur / BASE;
    }
    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator/=(int const &rhs) {
    if (rhs == 0) {
        throw new std::runtime_error("Division by zero!");
    }

    sign = sign * ((rhs < 0) ? -1 : 1);

    int r = (rhs < 0 ? -rhs : rhs);
    int carry = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        ll cur = digits[i] + carry * 1LL * BASE;
        digits[i] = cur / r;
        carry = cur % r;
    }
    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    // DBZ
    if (rhs.sign == 0) {
        throw new std::runtime_error("Division by zero!");
    }

    if (rhs.digits.size() == 1) {
        uint r = rhs.digits[0];
        ull carry = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            ull cur = digits[i] + carry * 1LL * BASE;
            digits[i] = cur / (ull)r;
            carry = cur % (ull)r;
        }
        *this *= rhs.sign;
        __remove_leading_zeros();
        return *this;
    }
    big_integer q = big_integer(), a = *this, b = rhs;
    a.sign = b.sign = 1;

    // a /= b, a < b -> a == 0
    if (a < b) {
        *this = ZERO;
        return *this;
    }

    uint scale = BASE / (b.digits[b.digits.size() - 1] + 1);
    if (scale > 1) {
        a *= scale;
        b *= scale;
    }

    int m = a.digits.size() - b.digits.size();
    int n = b.digits.size();
    q.digits.resize(a.digits.size() + 1);

    big_integer tmp;
    tmp = b;
    tmp.__shift_digits(m);
    if (a >= tmp) {
        q.digits[m] = 1;
        a -= tmp;
    } else {
        q.digits[m] = 0;
    }
    big_integer new_tmp;
    for (int j = m - 1; j >= 0; j--) {
        ull x = (ull)((int)a.digits.size() > n + j ? a.digits[n + j] : 0);
        ull y = (ull)((int) a.digits.size() > n + j - 1 ? a.digits[n + j - 1] : 0);
        ull qj = (x * (ull)BASE + y) / (ull)b.digits[b.digits.size() - 1];
        ull cur_qj = MIN(qj, (ull)BASE);
        q.digits[j] = cur_qj;

        if (cur_qj == 0) {
            continue;
        }

        tmp = b;
        tmp *= big_integer((uint)cur_qj);
        tmp.__shift_digits(j);
        a -= tmp;

        if (a.sign == -1) {
            new_tmp = b;
            new_tmp.__shift_digits(j);
            while (a.sign == -1) {
                q.digits[j]--;
                a += new_tmp;
            }
        }
    }

    q.sign = sign * rhs.sign;
    *this = q;
    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    if (sign == 0)
        return *this;

    *this -= (*this / rhs) * rhs;
    __remove_leading_zeros();
    return *this;
}

/* Operators &=, |=, ^= */

void big_integer::__apply_function(big_integer& a, big_integer const& b, int (*op)(int, int)) {
    if (a.sign == 0 || b.sign == 0) {
        a = ZERO;
        return;
    }
    
    char need_sign = ((*op)(a.sign == -1, b.sign == -1)) ? -1 : 1;
    big_integer r = big_integer(b);
    if (r.digits.size() > a.digits.size())
        a.digits.resize(r.digits.size());
    if (a.digits.size() > r.digits.size())
        r.digits.resize(a.digits.size());
    
    
    if (a.sign == -1)
        a.__additional_code();
    if (r.sign == -1)
        r.__additional_code();
    
    for (size_t i = 0; i < digits.size(); ++i)
        a.digits[i] = (*op)(a.digits[i], r.digits[i]);
    a.sign = need_sign;
    if (need_sign == -1)
        a.__additional_code();
    
    a.__remove_leading_zeros();
}


big_integer &big_integer::operator&=(big_integer const &rhs) {
    __apply_function(*this, rhs, [](int a, int b) { return a & b; });
    return *this;
}

big_integer &big_integer::operator|=(big_integer const &rhs) {
    __apply_function(*this, rhs, [](int a, int b) { return a | b; });
    return *this;
}

big_integer &big_integer::operator^=(big_integer const &rhs) {
    __apply_function(*this, rhs, [](int a, int b) { return a ^ b; });
    return *this;
}

/* Operators <<=, >>= */

big_integer &big_integer::operator<<=(int rhs) {
    if (rhs < 0) {
        throw new std::runtime_error("Shift length must be positive!");
    }
    if (sign == -1)
        __additional_code();

    int quot = rhs / BASE_LEN;
    int rem = rhs % BASE_LEN;
    if (rem) {
        ll carry = 0;
        for (size_t i = 0; i < digits.size() || carry; i++) {
            if (i == digits.size())
                digits.push_back(0);
            ll current = ((1LL * digits[i]) << rem) + carry;
            digits[i] = current & BASE;
            carry = current >> BASE_LEN;
        }
    }
    __shift_digits(quot);

    if (sign == -1)
        __additional_code();

    __remove_leading_zeros();
    return *this;
}

big_integer &big_integer::operator>>=(int rhs) {
    if (rhs < 0) {
        throw new std::runtime_error("Shift length must be positive!");
    }

    if (sign == -1)
        __additional_code();

    int quot = rhs / BASE_LEN;
    int rem = rhs % BASE_LEN;

    int new_size = digits.size() - quot;
    for (size_t i = quot; i < digits.size(); ++i)
        digits[i - quot] = digits[i];
    for (size_t i = digits.size() - quot; i < digits.size(); ++i)
        digits[i] = 0;
    digits.resize(new_size);

    if (rem) {
        ll carry = 0;
        if (sign == -1)
            carry = BASE;
        int power = BASE_LEN - rem;
        for (int i = (int)digits.size() - 1; i >= 0; i--) {
            ll shl = (1LL * digits[i]) >> rem;
            ll current = shl + (carry << power);
            carry = digits[i] - (shl << rem);
            digits[i] = current & BASE;
        }
    }

    if (sign == -1)
        __additional_code();

    __remove_leading_zeros();
    return *this;
}

/* Operators ==, !=, <, >, <=, >= */

bool operator==(big_integer const &a, big_integer const &b) {
    if ((a.sign != b.sign) || (a.digits.size() != b.digits.size())) {
        return false;
    }
    for (size_t i = 0; i < a.digits.size(); ++i)
        if (a.digits[i] != b.digits[i])
            return false;
    return true;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}

bool operator<(big_integer const &a, big_integer const &b) {
    if (a.sign != b.sign)
        return a.sign < b.sign;
    if (a.digits.size() != b.digits.size()) {
        if (a.sign == 1) {
            return a.digits.size() < b.digits.size();
        } else {
            return a.digits.size() > b.digits.size();
        }
    }
    for (int i = (int)a.digits.size() - 1; i >= 0; i--) {
        if (a.digits[i] != b.digits[i]) {
            if (a.sign == 1) {
                return a.digits[i] < b.digits[i];
            } else {
                return a.digits[i] > b.digits[i];
            }
        }
    }
    return false;
}

bool operator>(big_integer const &a, big_integer const &b) {
    return !(a <= b);
}

bool operator<=(big_integer const &a, big_integer const &b) {
    if (a.sign != b.sign)
        return a.sign < b.sign;
    if (a.digits.size() != b.digits.size()) {
        if (a.sign == 1) {
            return a.digits.size() < b.digits.size();
        } else {
            return a.digits.size() > b.digits.size();
        }
    }
    for (int i = (int)a.digits.size() - 1; i >= 0; i--) {
        if (a.digits[i] != b.digits[i]) {
            if (a.sign == 1) {
                return a.digits[i] < b.digits[i];
            } else {
                return a.digits[i] > b.digits[i];
            }
        }
    }
    return true;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return !(a < b);
}

/* Operators +, -, ~ (unary) */

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    if (sign == 0) {
        return *this;
    }
    big_integer nw = *this;
    nw.sign = ((sign == 1) ? -1 : 1);
    return nw;
}

big_integer big_integer::operator~() const {
    return -(*this + 1);
}

big_integer &big_integer::operator++() {
    *this += ONE;
    return *this;
}

big_integer big_integer::operator++(int i) {
    big_integer tmp = *this;
    ++*this;
    return tmp;
}

big_integer &big_integer::operator--() {
    *this -= ONE;
    return *this;
}

big_integer big_integer::operator--(int i) {
    big_integer tmp = *this;
    --(*this);
    return tmp;
}

std::string to_string(big_integer const &a) {
    std::string result = "";
    if (a.sign == 0) {
        result = "0";
        return result;
    }
    big_integer b = a;
    b.sign = 1;
    big_integer mod;
    while (b > ZERO) {
        mod = b % 10;
        result += char('0' + mod.digits[0]);
        b /= 10;
    }
    if (a.sign == -1) {
        result += '-';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

/* Binary operations */

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}

big_integer operator*(big_integer a, int const &b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}

big_integer operator/(big_integer a, int const &b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

std::ostream &operator<<(std::ostream &s, big_integer const &a) {
    return s << to_string(a);
}
