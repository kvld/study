#include <memory>
#include <iostream>
#include "persistent_bst.h"
#include "node.h"

using node = set::node;
using value_type = set::value_type;
using node_ptr = set::node_ptr;
using std::shared_ptr;
using std::make_shared;

set::set() : __root(nullptr) {
    
}

set::set(set const& other) {
    /*if (other.__root == nullptr) {
        __root = nullptr;
        return;
    }
    __root = make_shared<node>(other.__root->get_left(), other.__root->get_right(), other.__root->get_value());
     */
    __root = other.__root;
}

set& set::operator=(set const& other) {
    if (this == &other || other.__root == nullptr) {
        return *this;
    }
    shared_ptr<node> new_root = make_shared<node>(other.__root->get_left(), other.__root->get_right(), other.__root->get_value());
    std::swap(__root, new_root);
    return *this;
}

bool set::empty() const {
    return (__root == nullptr);
}

void set::insert(value_type const& element) {
    if (contains(element)) {
        return;
    }
    __root = __insert(this->get_root(), element);
}

void set::erase(value_type const& element) {
    if (!contains(element)) {
        return;
    }
    __root = __erase(this->get_root(), element);
}

bool set::contains(value_type const& element) {
    return __contains(this->get_root(), element);
}

node_ptr set::__erase(node_ptr current_node, value_type const& element) {
    if (current_node == nullptr) {
        return current_node;
    }
    
    node_ptr new_node = make_shared<node>();
    if (element < current_node->get_value()) {
        node_ptr t = __erase(current_node->get_left(), element);
        
        new_node->set_left((t == nullptr) ? t : make_shared<node>(*t));
        new_node->set_right(current_node->get_right());
        new_node->set_value(current_node->get_value());
    } else if (element > current_node->get_value()) {
        /* WTF?? */
        node_ptr t = __erase(current_node->get_right(), element);
        
        new_node->set_right((t == nullptr) ? t : make_shared<node>(*t));
        new_node->set_left(current_node->get_left());
        new_node->set_value(current_node->get_value());
    } else if (current_node->get_left() != nullptr && current_node->get_right() != nullptr) {
        value_type min_value = __minimum(current_node->get_right())->get_value();
        node_ptr new_right = __erase(current_node->get_right(), min_value);
        
        new_node->set_value(min_value);
        new_node->set_left(current_node->get_left());
        new_node->set_right((new_right == nullptr) ? new_right : make_shared<node>(*new_right));
    } else {
        if (current_node->get_left() != nullptr) {
            new_node = current_node->get_left();
        } else {
            new_node = current_node->get_right();
        }
    }
    return new_node;
}

node_ptr set::__insert(node_ptr current_node, value_type const& element) {
    if (current_node == nullptr) {
        return make_shared<node>(nullptr, nullptr, element);
    }
    node_ptr new_node = make_shared<node>(nullptr, nullptr, current_node->get_value());
    if (element < current_node->get_value()) {
        new_node->set_left(__insert(current_node->get_left(), element));
        new_node->set_right(current_node->get_right());
    } else if (element > current_node->get_value()) {
        new_node->set_right(__insert(current_node->get_right(), element));
        new_node->set_left(current_node->get_left());
    }
    return new_node;
}

bool set::__contains(node_ptr current_node, value_type const& element) {
    if (current_node == nullptr) {
        return false;
    }
    if (current_node->get_value() == element) {
        return true;
    }
    if (current_node->get_value() < element) {
        return __contains(current_node->get_right(), element);
    } else {
        return __contains(current_node->get_left(), element);
    }
}

node_ptr set::__minimum(node_ptr current_node) {
    if (current_node->get_left() == nullptr) {
        return current_node;
    }
    return __minimum(current_node->get_left());
}

void set::print_tree() {
    std::cerr << "b========" << std::endl;
    __print_tree(this->get_root(), 0);
    std::cerr << "e========" << std::endl;
}

void set::__print_tree(node_ptr current_node, size_t level) {
    if (current_node == nullptr)
        return;
    __print_tree(current_node->get_left(), level + 1);
    for (size_t i = 0; i < level; i++)
        std::cerr << ' ';
    std::cerr << current_node->get_value() << std::endl;
    __print_tree(current_node->get_right(), level + 1);
}