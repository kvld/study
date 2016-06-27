#include <memory>
#include <vector>
#include "deque.h"

/* Кажется, здесь есть баги в реализации */

using value_type = deque::value_type;
using iterator = deque::iterator;
using const_iterator = deque::const_iterator;

deque::deque() : __buffer(nullptr), __begin(*this, nullptr), __end(*this, nullptr), __size(0), __capacity(0) {
    
}

deque::deque(deque const& other) : __begin(*this, nullptr), __end(*this, nullptr) {
    __size = other.__size;
    __capacity = other.__capacity;
    __buffer = __reserve(__capacity);
    try {
        __copy(__buffer, other.__begin, other.__end, __size);
    } catch (std::exception &e) {
        operator delete (__buffer);
        throw;
    }
    __begin = iterator(*this, __buffer);
    __end = iterator(*this, std::max(__buffer, __buffer + __size - 1));
}


deque::~deque() {
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
}

iterator deque::begin() {
    return __begin;
}

const_iterator deque::begin() const {
    return __begin;
}

iterator deque::end() {
    return __end + 1;
}

const_iterator deque::end() const {
    return __end + 1;
}

deque& deque::operator=(deque const& other) {
    if (this == &other) {
        return *this;
    }
    value_type* new_buffer = __reserve(__capacity);
    try {
        __copy(new_buffer, other.__begin, other.__end, __size);
    } catch (std::exception &e) {
        operator delete (new_buffer);
        throw;
    }
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
    __buffer = new_buffer;
    __size = other.__size;
    __begin = iterator(other.__begin);
    __end = iterator(other.__end);
    __capacity = other.__capacity;
    return *this;
}

void deque::push_back(value_type const& element) {
    if (__size == __capacity) {
        size_t new_capacity = std::max(DEFAULT_BUFFER_SIZE, 2 * __capacity);
        value_type* new_buffer = __reserve(new_capacity);
        try {
            __copy(new_buffer, __begin, __end, __size);
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
        __begin = iterator(*this, __buffer);
        __end = iterator(*this, __buffer + __size);
        __capacity = new_capacity;
        __size++;
        
    } else {
        new (__buffer + __size) value_type(element);
        __end = iterator(*this, __buffer + __size);
        __size++;
    }
}

void deque::push_front(value_type const& element) {
    if (__size == __capacity) {
        size_t new_capacity = std::max(DEFAULT_BUFFER_SIZE, 2 * __capacity);
        value_type* new_buffer = __reserve(new_capacity);
        try {
            __copy(new_buffer + 1, __begin, __end, __size);
        } catch (std::exception &e) {
            operator delete (new_buffer);
            throw;
        }
        try {
            new (new_buffer) value_type(element);
        } catch (std::exception &e) {
            __clear_buffer(new_buffer, __size);
            operator delete (new_buffer);
            throw;
        }
        __clear_buffer(__buffer, __size);
        operator delete (__buffer);
        __buffer = new_buffer;
        __begin = iterator(*this, __buffer);
        __end = iterator(*this, __buffer + __size);
        __capacity = new_capacity;
        __size++;
        
    } else {
        iterator begin = __begin;
        --begin;
        new (&*begin) value_type(element);
        __begin = iterator(*this, &*begin);
        __size++;
    }
}

value_type& deque::front() {
    return *__begin;
}

value_type& deque::back() {
    return *__end;
}

value_type const& deque::back() const {
    return *__end;
}

value_type const& deque::front() const {
    return *__begin;
}

void deque::pop_front() {
    (&*__begin)->~value_type();
    ++__begin;
    --__size;
}

void deque::pop_back() {
    (&*__end)->~value_type();
    --__end;
    --__size;
}

bool deque::empty() const {
    return (__size == 0);
}

size_t deque::size() const {
    return __size;
}

value_type& deque::operator[](size_t index) {
    return *(__begin + index);
}

value_type const& deque::operator[](size_t index) const {
    return *(__begin + index);
}

iterator deque::erase(iterator pos) {
    value_type* new_buffer = __reserve(__capacity);
    iterator return_pos = pos;
    try {
        int offset = 0;
        for (iterator i = begin(); i != end(); ++i) {
            if (i == pos) {
                return_pos = iterator(*this, new_buffer + offset);
                continue;
            }
            new (new_buffer + offset) value_type(*i);
            offset++;
        }
    } catch (std::exception &e) {
        operator delete (new_buffer);
        throw;
    }
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
    __buffer = new_buffer;
    __begin = iterator(*this, __buffer);
    __end = iterator(*this, std::max(__buffer, __buffer + __size - 1));
    __size--;
    return return_pos;
}

iterator deque::insert(iterator pos, value_type const& element) {
    value_type* new_buffer = __reserve(__capacity);
    iterator return_pos = pos;
    try {
        int offset = 0;
        for (iterator i = begin(); i != end(); ++i) {
            if (i == pos) {
                return_pos = iterator(*this, new_buffer + offset);
                new (new_buffer + offset) value_type(element);
                offset++;
            }
            new (new_buffer + offset) value_type(*i);
            offset++;
        }
    } catch (std::exception &e) {
        operator delete (new_buffer);
        throw;
    }
    __clear_buffer(__buffer, __size);
    operator delete (__buffer);
    __buffer = new_buffer;
    __begin = iterator(*this, __buffer);
    __end = iterator(*this, std::max(__buffer, __buffer + __size - 1));
    __size++;
    return ++return_pos;
}

value_type* deque::__reserve(size_t new_size) {
    return reinterpret_cast<value_type *>(operator new(new_size * sizeof(value_type)));
}


void deque::__copy(value_type* new_buffer, iterator begin, iterator end, size_t size) {
    int offset = 0;
    try {
        for (iterator i = begin; i != end; ++i) {
            new (new_buffer + offset) value_type(*i);
            offset++;
        }
    } catch (std::exception &e) {
        for (size_t i = 0; i < offset; i++) {
            (new_buffer + offset)->~value_type();
        }
        throw e;
    }
}

void deque::__clear_buffer(value_type* buffer, size_t size) {
    value_type* begin = buffer;
    for (size_t i = 0; i < size; i++) {
        (begin + i)->~value_type();
    }
}