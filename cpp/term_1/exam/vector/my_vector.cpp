#include <memory>
#include <vector>
#include "my_vector.h"

using value_type = vector::value_type;
using iterator = vector::iterator;
using const_iterator = vector::const_iterator;

vector::vector() : __buffer(nullptr), __size(0), __capacity(0) {
    
}

vector::vector(vector const& other) : __size(other.__size), __capacity(other.__capacity) {
    __buffer = __reserve(__capacity);
    try {
        __copy(__buffer, other.__buffer, __size);
    } catch (std::exception &e) {
        operator delete (__buffer);
        throw;
    }
}

vector::~vector() {
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
}

vector& vector::operator=(vector const& other) {
    if (this == &other) {
        return *this;
    }
    iterator new_buffer = __reserve(__capacity);
    try {
        __copy(new_buffer, other.__buffer, __size);
    } catch (std::exception &e) {
        operator delete (new_buffer);
        throw;
    }
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
    __size = other.__size;
    __capacity = other.__capacity;
    __buffer = new_buffer;
    return *this;
}

void vector::clear() {
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
    __buffer = nullptr;
    __size = 0;
}

void vector::push_back(value_type element) {
    if (__size == __capacity) {
        size_t new_capacity = std::max(DEFAULT_BUFFER_SIZE, 2 * __capacity);
        iterator new_buffer = __reserve(new_capacity);
        try {
            __copy(new_buffer, __buffer, __size);
        } catch (std::exception &e) {
            operator delete (new_buffer);
            throw;
        }
        try {
            new (new_buffer + __size) value_type(element);
        } catch (std::exception &e) {
            __clear_buffer(new_buffer, __size);
            operator delete (new_buffer);
            throw;
        }
        __clear_buffer(__buffer, __size);
        operator delete (__buffer);
        __buffer = new_buffer;
        __capacity = new_capacity;
        __size++;
        
    } else {
        new (__buffer + __size) value_type(element);
        __size++;
    }
}

void vector::pop_back() {
    (end() - 1)->~value_type();
    __size--;
}

value_type& vector::back() {
    return __buffer[__size - 1];
}

value_type const& vector::back() const {
    return __buffer[__size - 1];
}

size_t vector::size() const {
    return __size;
}

value_type& vector::operator[](size_t index) {
    return __buffer[index];
}

value_type const& vector::operator[](size_t index) const {
    return __buffer[index];
}

iterator vector::begin() {
    return __buffer;
}

const_iterator vector::begin() const {
    return __buffer;
}

iterator vector::end() {
    return __buffer + __size;
}

const_iterator vector::end() const {
    return __buffer + __size;
}


iterator vector::erase(iterator pos) {
    for (iterator i = pos; i != end(); i++) {
        std::swap(*i, *(i + 1));
    }
    (end() - 1)->~value_type();
    __size--;
    return pos;
}

iterator vector::erase(iterator begin, iterator end) {
    int c = 0;
    for (iterator i = end; i != this->end(); i++) {
        std::swap(*(begin + c), *i);
        c++;
        if (begin + c > end) {
            break;
        }
    }
    for (iterator i = end; i != this->end(); i++) {
        std::swap(*i, *(i + 1));
    }
    c = (end - begin);
    for (iterator i = this->end() - 1; c >= 0; i--) {
        i->~value_type();
        c--;
    }
    __size -= (end - begin);
    return end;
}

iterator vector::insert(iterator pos, value_type const& element) {
    this->push_back(element);
    for (iterator i = this->end() - 1; i > pos; i--) {
        std::swap(*i, *(i - 1));
    }
    *pos = element;
    return pos;
}

iterator vector::__reserve(size_t new_size) {
    return reinterpret_cast<iterator>(operator new(new_size * sizeof(value_type)));
}


void vector::__copy(iterator new_buffer, iterator old_buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        new (new_buffer) value_type(*old_buffer);
        new_buffer++;
        old_buffer++;
    } // надо почистить память, которую навыделяли с new, если он упал на какой-то итерации
}

void vector::__clear_buffer(iterator buffer, size_t size) {
    iterator begin = buffer;
    for (size_t i = 0; i < size; i++) {
        (begin + i)->~value_type();
    }
}