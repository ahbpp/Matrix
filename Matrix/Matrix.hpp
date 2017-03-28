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
#include <cstring>

using namespace std;

template <typename T>
class Matrix {
private:
    size_t raw_count;
    size_t col_count;
    T **values;
public:
    Matrix(const Matrix<T> &);
    Matrix(size_t, size_t);
    ~Matrix();
    T get (size_t, size_t) const;
    void set (size_t, size_t, T);
    template <typename C>
    friend istream& operator>>(istream& in, const Matrix<C> &a);
    template <typename C>
    friend ostream& operator<<(ostream& res, const Matrix<C> &a);
    friend Matrix<T> operator*(const int k, const Matrix &a);
    Matrix operator+(const Matrix &);
    Matrix operator*(const Matrix &);
    Matrix operator*(const int k);
    void print ();
};

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &old)
{
    this->raw_count = old.raw_count;
    this->col_count = old.col_count;
    this->values = new T *[this->raw_count];
    for (int i = 0; i < this->raw_count; i++)
    {
        this->values[i] = new T[this->col_count];
    }
    for (int i = 0; i < this->raw_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->values[i][j] = old.values[i][j];
        }
    }
}
template <typename T>
Matrix<T>::Matrix(size_t raw_count, size_t col_count):
raw_count(raw_count), col_count(col_count)
{
    this->values = new T *[this->raw_count];
    for (int i = 0; i < this->raw_count; i++)
    {
        this->values[i] = new T[this->col_count];
    }
    for (int i = 0; i < raw_count; i++)
    {
        for (int j = 0; j < col_count; j++)
        {
            this->values[i][j] = 0;
        }
    }
}
template <typename T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < this->raw_count; i++)
        delete [] this->values[i];
    delete [] this->values;
}
template <typename T>
void Matrix<T>::set(size_t i, size_t j, T val)
{
    this->values[i][j] = val;
}
template <typename T>
T Matrix<T>::get(size_t i, size_t j) const
{
    return this->values[i][j];
}
template <typename C>
istream& operator>>(istream &in, const Matrix<C> &a)
{
    for (int i = 0; i < a.raw_count; i++)
    {
        for (int j = 0; j < a.col_count; j++)
            in >> a.values[i][j];
    }
    return in;
}
template <typename C>
ostream& operator<<(ostream& res, const Matrix<C> &a)
{
    for (int i = 0; i < a.raw_count; i++)
    {
        for (int j = 0; j < a.col_count; j++)
            res << a.values[i][j] << " ";
        res << endl;
    }
    return res;
}
template <typename T>
Matrix<T> operator*(const int k, const Matrix<T> &a) {
    Matrix<T> res(a.raw_count, a.col_count);
    for (int i = 0; i < a.raw_count; i++)
    {
        for (int j = 0; j < a.col_count; j++)
        {
            res.values[i][j] = a.values[i][j] * k;
        }
    }
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &that)
{
    if (this->raw_count == that.raw_count && this->col_count == that.col_count)
    {
        Matrix res(this->raw_count, this->col_count);
        for (int i = 0; i < this->raw_count; i++)
        {
            for (int j = 0; j < this->col_count; j++)
            {
                res.values[i][j] = this->values[i][j] + that.values[i][j];
            }
        }
        return res;
    } else {
        cout << "error" << endl;
        return that;
    }
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &that)
{
    if (this->col_count == that.raw_count)
    {
        Matrix res(this->raw_count, that.col_count);
        for (int i = 0; i < res.raw_count; i++)
        {
            for (int j = 0; j < res.col_count; j++)
            {
                res.values[i][j] = 0;
                for (int q = 0; q < this->col_count; q++)
                {
                    res.values[i][j] += this->values[i][q] * that.values[q][j];
                }
            }
        }
        return res;
    }else{
        cout << "error" << endl;
        return that;
    }
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const int k)
{
    Matrix res(this->raw_count, this->col_count);
    for (int i = 0; i < this->raw_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            res.values[i][j] = this->values[i][j] * k;
        }
    }
    return res;
}

template <typename T>
void Matrix<T>::print()
{
    for (int i = 0; i < raw_count; i++)
    {
        for (int j = 0; j < col_count; j++)
            cout << values[i][j] << " ";
        cout << endl;
    }
}

#endif /* Matrix_hpp */
