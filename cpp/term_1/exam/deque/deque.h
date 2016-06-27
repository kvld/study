#ifndef DEQUE_H
#define DEQUE_H
#include <string>

const size_t DEFAULT_BUFFER_SIZE = 12;

struct deque {
    typedef std::string value_type;
    
    struct iterator {
        value_type& operator*();
        value_type const& operator*() const;
        value_type* operator->();
        
        iterator(iterator const& other);
        iterator(deque& parent);
        iterator(deque& parent, value_type* ptr);
        ~iterator();
        
        iterator& operator=(iterator const& other);
        
        bool operator==(iterator const& other) const;
        bool operator!=(iterator const& other) const;
        
        bool operator<(iterator const& other) const;
        bool operator<=(iterator const& other) const;
        bool operator>(iterator const& other) const;
        bool operator>=(iterator const& other) const;
        
        iterator& operator++();
        iterator& operator--();
        iterator& operator+=(int const& other);
        iterator& operator-=(int const& other);
        
        value_type* __ptr;
        deque* __parent;
    };

    struct const_iterator {
        value_type const& operator*();
        value_type const* operator->();
        
        const_iterator(deque& parent);
        const_iterator(iterator const& parent);
        const_iterator(deque& parent, value_type* ptr);
        ~const_iterator();
        
        bool operator==(const_iterator const& other) const;
        bool operator!=(const_iterator const& other) const;
        
        bool operator<(const_iterator const& other) const;
        bool operator<=(const_iterator const& other) const;
        bool operator>(const_iterator const& other) const;
        bool operator>=(const_iterator const& other) const;
        
        
    private:
        value_type const* __ptr;
        deque* __parent;
    };
    
    deque();
    deque(deque const& other);
    ~deque();
    
    deque& operator=(deque const& other);
    
    void push_back(value_type const& element);
    void pop_back();
    value_type& back();
    value_type const& back() const;
    value_type& front();
    value_type const& front() const;
    void push_front(value_type const& element);
    void pop_front();
    size_t size() const;
    bool empty() const;
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    
    iterator erase(iterator pos);
    iterator insert(iterator pos, value_type const& element);
    
    value_type& operator[](size_t index);
    value_type const& operator[](size_t index) const;
    
private:
    value_type* __buffer;
    iterator __begin;
    iterator __end;
    size_t __size;
    size_t __capacity;
    
    value_type* __reserve(size_t size);
    void __copy(value_type* new_buffer, iterator begin, iterator end, size_t size);
    void __clear_buffer(value_type* buffer, size_t size);
    
};

deque::iterator operator+(deque::iterator a, int const& b);
deque::iterator operator-(deque::iterator a, int const& b);
deque::iterator operator+(int const& a, deque::iterator b);


#endif // DEQUE_H