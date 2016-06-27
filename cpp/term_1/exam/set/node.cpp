#include "node.h"

using node = set::node;
using value_type = set::value_type;

node::node() : __left(nullptr), __right(nullptr), __value(value_type()) {
    
}

node::node(node const& other) : __left(other.__left), __right(other.__right), __value(other.__value) {
    
}

node::node(set::node_ptr left, set::node_ptr right, value_type value) : __left(left), __right(right), __value(value) {
    
}

set::node_ptr node::get_left() {
    return __left;
}

set::node_ptr node::get_right() {
    return __right;
}

value_type node::get_value() {
    return __value;
}

void node::set_left(set::node_ptr new_left) {
    __left = new_left;
}

void node::set_right(set::node_ptr new_right) {
    __right = new_right;
}

void node::set_value(value_type value) {
    __value = value;
}
