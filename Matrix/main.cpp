//
//  main.cpp
//  Matrix
//
//  Created by Alexey Karpov on 28.02.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"

using namespace mipt;
using namespace std;

int main() {
    Matrix a(2, 2);
    cin >> a;
    Matrix b(a);
    cout << b << endl;
    cout << a << endl;
    a.set(1, 1, 6);
    cout << a << endl;
    cout << a.get(1, 1) << endl;
    cout << a + b << endl;
    cout << a * b << endl;
    cout << a * 2 << endl;
    cout << 3 * a << endl;
    cout << Matrix::count << endl;
    return 0;
}
