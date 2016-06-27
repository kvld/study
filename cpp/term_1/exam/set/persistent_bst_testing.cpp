#include <iostream>
#include <cassert>
#include "persistent_bst.h"

using namespace std;


int main() {
    
    set a;
    
    assert(a.empty());
    cout << "empty " << a.empty() << endl;
    
    a.insert("1");
    a.insert("2");
    
    assert(!a.empty());
    cout << "empty " << a.empty() << endl;
    cout << "contains 1 " << a.contains("1") << endl;
    cout << "contains 2 " << a.contains("2") << endl;
    
    set b = a;
    b.insert("0");
    cout << "contains a:0 " << a.contains("0") << endl;
    cout << "contains b:0 " << b.contains("0") << endl;
    
    b.erase("1");
    cout << "contains b:1 " << b.contains("1") << endl;
    
    a.insert("5");
    a.insert("0");
    a.print_tree();
    
    set c;
    c.insert("5");
    c.insert("6");
    c.insert("7");
    c.insert("4");
    c.insert("2");
    b = c;
    b.print_tree();
    c.insert("0");
    c.insert("3");
    c.print_tree();
    b.print_tree();
    
    a = c;
    a.erase("7");
    a.print_tree();
    c.print_tree();
    a.erase("4");
    a.print_tree();
    
    set aa, bb;
    aa.insert("2");
    aa.insert("1");
    aa.insert("3");
    bb = aa;
    aa.insert("4");
    aa.erase("1");
    bb.insert("5");
    bb.erase("2");
    
    aa.print_tree();
    bb.print_tree();
    
    
    set cc;
    cc.insert("0");
    cc.erase("0");
    cout << cc.empty() << endl;
    set dd;
    dd = cc;
    
    set nn;
    for(int i = 1; i <= 1000; i++)
        nn.insert(std::to_string(i));
    
    for(int i = 1; i <= 1000; i++)
        nn.erase(std::to_string(i));
    
    nn.print_tree();
    std::cout << nn.empty();
    
}