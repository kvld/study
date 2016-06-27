#ifndef ITERATOR_CPP
#define ITERATOR_CPP
#include "deque.h"

using value_type = deque::value_type;
using iterator = deque::iterator;

deque::iterator::iterator(deque& p) : __ptr(nullptr), __parent(&p) {
    
}

deque::iterator::iterator(iterator const& other) : __ptr(other.__ptr), __parent(other.__parent) {
    
}

deque::iterator::iterator(deque& parent, value_type* ptr) : __ptr(ptr), __parent(&parent) {
    
}

deque::iterator::~iterator() {
    
}

iterator& iterator::operator=(iterator const& other) {
    __parent = other.__parent;
    __ptr = other.__ptr;
    return *this;
}

value_type& deque::iterator::operator*() {
    return *__ptr;
}

value_type const& deque::iterator::operator*() const {
    return *__ptr;
}

value_type* deque::iterator::operator->() {
    return __ptr;
}

bool deque::iterator::operator==(iterator const& other) const {
    return (__ptr == other.__ptr);
}

bool deque::iterator::operator!=(iterator const& other) const {
    return (__ptr != other.__ptr);
}

bool deque::iterator::operator<(iterator const& other) const {
    if (this->operator==(other))
        return false;
    if (__parent->__begin < __parent->__end) {
        return __ptr < other.__ptr;
    } else {
        if (__ptr > __parent->__begin.__ptr && other.__ptr > __parent->__begin.__ptr)
            return __ptr < other.__ptr;
        if (__ptr < __parent->__end.__ptr && other.__ptr < __parent->__end.__ptr)
            return __ptr < other.__ptr;
        if (__ptr < __parent->__end.__ptr && other.__ptr > __parent->__begin.__ptr)
            return false;
        if (__ptr > __parent->__begin.__ptr && other.__ptr < __parent->__end.__ptr)
            return true;
    }
    return true;
}

bool deque::iterator::operator>(iterator const& other) const {
    if (this->operator==(other))
        return false;
    if (__parent->__begin < __parent->__end) {
        return __ptr > other.__ptr;
    } else {
        if (__ptr > __parent->__begin.__ptr && other.__ptr > __parent->__begin.__ptr)
            return __ptr > other.__ptr;
        if (__ptr < __parent->__end.__ptr && other.__ptr < __parent->__end.__ptr)
            return __ptr > other.__ptr;
        if (__ptr < __parent->__end.__ptr && other.__ptr > __parent->__begin.__ptr)
            return true;
        if (__ptr > __parent->__begin.__ptr && other.__ptr < __parent->__end.__ptr)
            return false;
    }
    return false;
}

bool deque::iterator::operator<=(iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}

bool deque::iterator::operator>=(iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}


iterator& deque::iterator::operator++() {
    __ptr++;
    if (__ptr > (__parent->__buffer + __parent->__capacity)) {
        __ptr = __parent->__buffer;
    }
    return *this;
}

iterator& deque::iterator::operator--() {
    __ptr--;
    if (__ptr < __parent->__buffer) {
        __ptr = __parent->__buffer + __parent->__capacity;
    }
    return *this;
}

iterator& deque::iterator::operator+=(int const& other) {
    if (other == 0)
        return *this;
    if (other < 0) {
        return this->operator-=(-other);
    }
    ptrdiff_t dist_to_end = __parent->__buffer + __parent->__capacity - __ptr;
    int len = other;
    if (dist_to_end >= len)
        __ptr += len;
    else {
        len -= dist_to_end;
        __ptr = __parent->__buffer + len - 1;
    }
    return *this;
}

iterator& deque::iterator::operator-=(int const& other) {
    if (other == 0)
        return *this;
    if (other < 0) {
        return this->operator+=(-other);
    }
    ptrdiff_t dist_to_begin = __ptr - __parent->__buffer;
    int len = other;
    if (dist_to_begin < len)
        __ptr -= len;
    else {
        len -= dist_to_begin;
        __ptr = __parent->__buffer + __parent->__capacity - len;
    }
    return *this;
}

deque::iterator operator+(deque::iterator a, int const& b) {
    return a += b;
}

deque::iterator operator-(deque::iterator a, int const& b) {
    return a -= b;
}

deque::iterator operator+(int const& a, deque::iterator b) {
    return b += a;
}


#endif