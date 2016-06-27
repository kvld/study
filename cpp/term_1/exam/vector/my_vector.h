#ifndef my_vector_cpp_my_vector_h
#define my_vector_cpp_my_vector_h

#include <string>

const size_t DEFAULT_BUFFER_SIZE = 12;

struct vector {
    typedef std::string value_type;
    typedef value_type* iterator;
    typedef value_type const* const_iterator;
    
    vector();
    vector(vector const& other);
    ~vector();
    
    vector& operator=(vector const& other);
    
    void clear();
    void push_back(value_type element);
    void pop_back();
    value_type& back();
    value_type const& back() const;
    size_t size() const;
    
    value_type& operator[](size_t index);
    value_type const& operator[](size_t index) const;
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    

    iterator erase(iterator pos);
    iterator erase(iterator begin, iterator end);
    
    iterator insert(iterator pos, value_type const& element);
    
private:
    void __copy(iterator new_buffer, iterator old_buffer, size_t size);
    void __clear_buffer(iterator buffer, size_t size);
    iterator __reserve(size_t new_size);
    iterator __buffer;
    size_t __size;
    size_t __capacity;
    
};

#endif
