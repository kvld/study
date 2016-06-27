#ifndef BIG_INTEGER_CPP_CUSTOM_VECTOR_H
#define BIG_INTEGER_CPP_CUSTOM_VECTOR_H

#include <vector>
#include <algorithm>
#include <memory>

typedef unsigned int uint;
typedef std::vector<uint> vector_uint;

class custom_vector {
public:
    custom_vector();
    custom_vector(size_t n);
    custom_vector(custom_vector const& other);
    ~custom_vector();

    void resize(size_t new_size);
    void push_back(uint x);
    void pop_back();
    void clear();
    void copy(size_t size);
    custom_vector& operator=(custom_vector const &other);
    uint& operator[](const size_t k);
    uint const& operator[](const size_t k) const;
    
    size_t size() const {
        return length;
    }

private:
    std::shared_ptr<vector_uint> a;
    uint small_a;
    bool is_small;
    size_t length;
};

#endif //BIG_INTEGER_CPP_CUSTOM_VECTOR_H
