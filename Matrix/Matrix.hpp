//
//  Matrix.hpp
//  Matrix
//
//  Created by Alexey Karpov on 28.02.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef int cell;
namespace mipt {
    class Matrix {
    private:
        size_t raw_count;
        size_t col_count;
        cell **values;
    public:
        Matrix(const Matrix &);
        Matrix(size_t, size_t);
        ~Matrix();
        cell get (size_t, size_t) const;
        void set (size_t, size_t, cell);
        friend istream& operator>>(istream& in, const Matrix &a);
        friend ostream& operator<<(ostream& res, const Matrix &a);
        friend Matrix operator*(const int k, const Matrix &a);
        Matrix operator+(const Matrix &);
        Matrix operator*(const Matrix &);
        Matrix operator*(const int k);
        static int count;
    };
}
#endif /* Matrix_hpp */
