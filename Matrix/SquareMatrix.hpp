//
//  SquareMatrix.hpp
//  Matrix
//
//  Created by Alexey Karpov on 28.03.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#ifndef SquareMatrix_hpp
#define SquareMatrix_hpp

#include "Matrix.hpp"

using namespace std;

template <typename T>
class SquareMatrix : public Matrix<T> {
private:
    void assign(const Matrix<T> &that);
     SquareMatrix ();
public:
    SquareMatrix (int size);
    SquareMatrix (const Matrix<T> &that);
    int getSize () const;
    SquareMatrix operator-(const SquareMatrix &) const;
    SquareMatrix operator+(const SquareMatrix &) const;
    SquareMatrix operator*(const SquareMatrix &) const;
    SquareMatrix &operator=(const SquareMatrix<T> &);
    SquareMatrix operator*(const T k) const;
    SquareMatrix &operator+=(const SquareMatrix &);
    SquareMatrix &operator-=(const SquareMatrix &);
    SquareMatrix &operator*=(const SquareMatrix &);
    SquareMatrix &operator*=(const T k);
    template <typename C>
    friend Matrix<C> operator*(const C k, const Matrix<C> &a);
    SquareMatrix minor(int i, int j) const;
    T getDeterminant()  const;
    SquareMatrix getInverse() const;
    SquareMatrix getTransposed () const;
    SquareMatrix &transpose ();
    SquareMatrix<T> &invert();
    T getTrace() const;
};
template <typename T>
void SquareMatrix<T>::assign(const Matrix<T> &that)
{
    Matrix<T>::assign(that);
}

template <typename T>
SquareMatrix<T>::SquareMatrix(int size){
    Matrix<T>::set_memory(size, size);
    for (int i = 0; i < Matrix<T>::getRowsNumber(); i++)
    {
        for (int j = 0; j < Matrix<T>::getColumnsNumber(); j++)
        {
            Matrix<T>::set (i, j, 0);
        }
    }
}
template <typename T>
SquareMatrix<T>::SquareMatrix(){}

template <typename T>
SquareMatrix<T>::SquareMatrix(const Matrix<T> &that){
    assign(that);
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T> &that) const
{
   SquareMatrix res(Matrix<T>::operator+(that));
    return res;
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix<T> &that) const
{
    SquareMatrix res(Matrix<T>::operator-(that));
    return res;
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T> &that) const
{
    SquareMatrix res(Matrix<T>::operator*(that));
    return res;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator=(const SquareMatrix<T> &that)
{
    if (this != &that)
    {
        Matrix<T>::free_memory();
        assign(that);
    }
    return *this;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator+=(const SquareMatrix &that)
{
    *this = *this + that;
    return *this;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator-=(const SquareMatrix &that)
{
    *this = *this - that;
    return *this;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const SquareMatrix &that)
{
    *this = *this * that;
    return *this;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const T k)
{
    *this = *this * k;
    return *this;
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T k) const
{
    SquareMatrix res(Matrix<T>::operator*(k));
    return res;
}
template <typename C>
SquareMatrix<C> operator*(const C k, const SquareMatrix<C> &a)
{
    return a * k;
}
template <typename T>
int SquareMatrix<T>::getSize() const
{
    return this->Matrix<T>::getRowsNumber();
}
template <typename T>
T SquareMatrix<T>::getDeterminant()  const
{
    SquareMatrix<T> temp(*this);
    bool flag = true;
    T det = T(1);
    for (int col = 0; col < temp.getSize() && flag == true; col++) {
        int j = col;
        while (j < temp.getSize() && temp.Matrix<T>::get(j,col) == T(0)) {
            j++;
        }
        if (j == temp.getSize()) {
            flag = false;
        }
        else {
            if (j != col) {
                temp.Matrix<T>::swap_rows(col, j);
            }
            for (int k = col + 1; k < temp.getSize(); k++)
            {
                T coef = temp.Matrix<T>::get(k, col) / temp.Matrix<T>::get(col, col);
                temp.Matrix<T>::row_sum_add(k, col, -coef);
            }
        }
        det *= temp.Matrix<T>::get(col, col);
    }
    if (!flag) {
        det = T(0);
    }
    return det;
    
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::minor(int row, int col) const
{
    SquareMatrix res;
    res.Matrix<T>::set_memory(getSize() - 1, getSize() - 1);
    for (int i = 0; i < res.getSize(); i++)
    {
        for (int j = 0; j < res.getSize(); j++)
        {
            int di = 0, dj = 0;
            if (i >= row)
                di = 1;
            if (j >= col)
                dj = 1;
            res.Matrix<T>::set(i, j, this->Matrix<T>::get(i + di, j + dj));
        }
    }
    return res;
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::getTransposed () const
{
    SquareMatrix res(getSize());
    for (int i = 0; i < getSize(); i++)
    {
        for (int j = 0; j < getSize(); j++)
        {
            res.Matrix<T>::set(i, j, this->Matrix<T>::get(j, i));
        }
    }
    return res;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::transpose()
{
    *this = getTransposed();
    return *this;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse() const
{
    if (this->getDeterminant() == T(0)) {
        throw MatrixIsDegenerateError();
    }
    SquareMatrix res;
    res.Matrix<T>::set_memory(getSize(), getSize());
    for (int i = 0; i < res.getSize(); i++)
    {
        for (int j = 0; j < res.getSize(); j++)
        {
            T a = 0;
            if ((i + j) % 2 == 0)
            {
                a =  minor(i, j).getDeterminant() ;
            } else {
                a = -minor(i, j).getDeterminant() ;
            }
            res.Matrix<T>::set(i, j, a);
        }
    }
    res = res.transpose();
    res *= (1 / getDeterminant());
    return res;
}
template <typename T>
SquareMatrix<T> &SquareMatrix<T>::invert()
{
    *this = getInverse();
    return *this;
}
template <typename T>
T SquareMatrix<T>::getTrace() const {
    T sum = 0;
    for (int i = 0; i < this->getSize(); i++) {
        sum += this->Matrix<T>::get(i, i);
    }
    return sum;
}


#endif /* SquareMatrix_hpp */
