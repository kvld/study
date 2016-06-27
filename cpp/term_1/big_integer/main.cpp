#include <stdio.h>
#include <iostream>
#include <vector>
#include "big_integer.h"
#include "custom_vector.h"

using namespace std;

int main() {
    custom_vector a, b;
    a.push_back(12);
    a.push_back(13);
    a.push_back(14);
    
    b = a;
    cout << a[0] << ' ' << b[0] << endl;
    
    a[0] = 11;
    cout << a[0] << ' ' << b[0] << endl;
    
    a.clear();
    cout << a[0] << ' ' << b[0] << endl;
}