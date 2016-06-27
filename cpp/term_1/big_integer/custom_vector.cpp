#include "custom_vector.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using std::cerr;
using std::endl;

custom_vector::custom_vector() {
    length = 0;
    small_a = 0;
    is_small = true;
}

custom_vector::custom_vector(size_t n) {
    length = n;
    if (n <= 1) {
        is_small = true;
        small_a = 0;
    } else {
        is_small = false;
        a = std::make_shared<vector_uint>(n);
    }
}

custom_vector::~custom_vector() {
    if (!is_small)
        a.reset();
}

void custom_vector::copy(size_t size) {
    if (is_small) {
        return;
    } else {
        vector_uint new_vec(a->begin(), a->begin() + size);
        a = std::make_shared<vector_uint>(new_vec);
    }
}

custom_vector::custom_vector(custom_vector const& other) {
    operator=(other);
}

custom_vector &custom_vector::operator=(custom_vector const &vec) {
    if (!is_small) {
        a.reset();
    }
    if (vec.is_small) {
        if (is_small) {
            small_a = vec.small_a;
            length = vec.length;
        } else {
            a.reset();
            small_a = vec.small_a;
            length = vec.length;
            is_small = true;
        }
    } else {
        if (is_small) {
            is_small = false;
            a = vec.a;
            length = vec.length;
        } else {
            length = vec.length;
            a = vec.a;
        }
    }
    return *this;
}

void custom_vector::resize(size_t n) {
    if (length == n) {
        return;
    }
    if (n > 1) {
        if (is_small) {
            a = std::make_shared<vector_uint>(n);
            a->operator[](0) = small_a;
            is_small = false;
        } else {
            if (!a.unique()) {
                copy(length);
            }
            a->resize(n, 0);
        }
    } else if (n <= 1) {
        if (is_small) {
            small_a = 0;
        } else {
            if (!a.unique()) {
                copy(1);
            }
            is_small = true;
            small_a = a->operator[](0);
            a.reset();
        }
    }
    length = n;
}

void custom_vector::push_back(uint x) {
    if (length == 0) {
        is_small = true;
        small_a = x;
    } else if (length == 1) {
        is_small = false;
        a.reset();
        a = std::make_shared<vector_uint>(2);
        a->operator[](0) = small_a;
        a->operator[](1) = x;
    } else {
        if (!a.unique()) {
            copy(length);
        }
        a->push_back(x);
    }
    length++;
}

void custom_vector::pop_back() {
    if (length == 0) {
        throw new std::runtime_error("Vector is empty!");
    }
    if (length == 1) {
        small_a = 0;
    } else if (length == 2) {
        small_a = a->operator[](0);
        a.reset();
        is_small = true;
    } else {
        if (!a.unique()) {
            copy(length - 1);
        } else {
            a->pop_back();
        }
    }
    length--;
}

void custom_vector::clear() {
    if (is_small) {
        small_a = 0;
    } else {
        a.reset();
        is_small = true;
        small_a = 0;
    }
    length = 0;
}

uint &custom_vector::operator[](const size_t k) {
    if (k > length) {
        throw new std::out_of_range("Range check error!");
    }
    if (is_small) {
        return small_a;
    } else {
        if (!a.unique()) {
            copy(length);
        }
        return a->operator[](k);
    }
}

uint const& custom_vector::operator[](const size_t k) const {
    if (k > length) {
        throw new std::out_of_range("Range check error!");
    }
    if (is_small) {
        return small_a;
    } else {
        return a->operator[](k);
    }
}
