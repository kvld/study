#ifndef persistent_bst_cpp_h
#define persistent_bst_cpp_h
#include <string>

struct set {
    typedef std::string value_type;
    
    struct node;
    typedef std::shared_ptr<node> node_ptr;
    
    set();
    set(set const& other);
    
    set& operator=(set const& other);
    
    bool empty() const;
    void insert(value_type const& element);
    void erase(value_type const& element);
    bool contains(value_type const& element);
    
    void print_tree();
    
    node_ptr get_root() {
        return __root;
    }
    
private:
    node_ptr __root;
    
    bool __contains(node_ptr current_node, value_type const& element);
    node_ptr __insert(node_ptr current_node, value_type const& element);
    node_ptr __erase(node_ptr current_node, value_type const& element);
    node_ptr __minimum(node_ptr current_node);
    void __print_tree(node_ptr current_node, size_t level);
};

#endif