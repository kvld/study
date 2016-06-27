#include "deque.h"

using value_type = deque::value_type;
using const_iterator = deque::const_iterator;

deque::const_iterator::const_iterator(deque& p) : __ptr(nullptr), __parent(&p) {
    
}

deque::const_iterator::const_iterator(iterator const& other) : __ptr(other.__ptr), __parent(other.__parent) {
    
}

deque::const_iterator::const_iterator(deque& parent, value_type* ptr) : __ptr(ptr), __parent(&parent) {
    
}

deque::const_iterator::~const_iterator() {
    
}
value_type const& deque::const_iterator::operator*() {
    return *__ptr;
}

value_type const* deque::const_iterator::operator->() {
    return __ptr;
}

bool deque::const_iterator::operator==(const_iterator const& other) const {
    return (__ptr == other.__ptr);
}

bool deque::const_iterator::operator!=(const_iterator const& other) const {
    return (__ptr != other.__ptr);
}

bool deque::const_iterator::operator<(const_iterator const& other) const {
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

bool deque::const_iterator::operator>(const_iterator const& other) const {
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

bool deque::const_iterator::operator<=(const_iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}

bool deque::const_iterator::operator>=(const_iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}

