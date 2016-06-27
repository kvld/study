#include <iostream>
#include "deque.h"

using iterator = deque::iterator;
using std::cout;
using std::endl;

void print(std::string desc, deque const& a) {
    cout << desc << endl;
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << ' ';
    cout << endl;
}

int main() {
    deque a;
    for (int i = 0; i < 20; i++)
        a.push_back(std::to_string(i));
    print("push_back", a);
    
    for (int i = 0; i < 20; i++)
        a[i] = std::to_string(i + 1);
    print("operator []", a);
    
    for (int i = 0; i < 19; i++)
        a[i] = a[i + 1];
    print("operator []", a);
    
    for (int i = 0; i < 10; i++)
        a.pop_back();
    print("10 pop_back()" , a);
    
    for (int i = 0; i < 20; i++)
        a.push_front(std::to_string(i + 2));
    print("20 push_front()" , a);
    
    for (int i = 0; i < 10; i++)
        a.pop_front();
    print("10 pop_front()" , a);
    
    a.pop_back();
    cout << "front " << a.front() << endl << "back " << a.back() << endl;
    cout << "size " << a.size() << endl;
    cout << "empty " << (a.empty() ? "true" : "false") << endl;
    
    deque e = a;
    print("before insert", e);
    e.insert(e.begin(), "x");
    print("insert in begin", e);
    e = a;
    e.insert(e.begin() + 3, "x");
    print("insert in 4th pos", e);
    e = a;
    e.erase(e.begin());
    print("erase from begin", e);
    e = a;
    e.erase(e.begin() + 3);
    print("erase from 4th pos", e);
}