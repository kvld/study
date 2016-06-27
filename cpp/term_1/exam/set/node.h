#ifndef persistent_bst_cpp_node_h
#define persistent_bst_cpp_node_h
#include "persistent_bst.h"

struct set::node {
    node();
    node(node const& other);
    node(set::node_ptr left, set::node_ptr right, value_type value);
    
    set::node_ptr get_left();
    set::node_ptr get_right();
    value_type get_value();
    
    void set_left(set::node_ptr new_left);
    void set_right(set::node_ptr new_right);
    void set_value(value_type value);
    
private:
    set::node_ptr __left;
    set::node_ptr __right;
    value_type __value;
};

#endif
