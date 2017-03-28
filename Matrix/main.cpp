//
//  main.cpp
//  Matrix
//
//  Created by Alexey Karpov on 28.02.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main() {
    Matrix<float> a(2, 2);
    cin >> a;
    cout << a;
    return 0;
}
