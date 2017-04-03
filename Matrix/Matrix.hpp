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
#include <stdexcept>

using namespace std;

class MatrixWrongSizeError : logic_error {
public:
    MatrixWrongSizeError();
};

MatrixWrongSizeError::MatrixWrongSizeError() : logic_error("Error") {}

class MatrixIndexError : logic_error {
public:
    MatrixIndexError();
};

MatrixIndexError::MatrixIndexError() : logic_error("Error") {}

class MatrixIsDegenerateError : logic_error {
public:
    MatrixIsDegenerateError();
};

MatrixIsDegenerateError::MatrixIsDegenerateError() : logic_error("Error") {}


template <typename T>
class Matrix {
private:
    int row_count;
    int col_count;
    T **values;
protected:
    Matrix();
    void assign(const Matrix &that);
    void set_memory(const int col_count, const int raw_count);
    void free_memory();
    void swap_rows(const int, const int);
    void row_sum_add(const int, const int, const T);
public:
    Matrix(const Matrix<T> &);
    Matrix(int, int);
    ~Matrix();
    T get (int, int) const;
    void set (int, int, T);
    template <typename C>
    friend istream& operator>>(istream& in, const Matrix<C> &a);
    template <typename C>
    friend ostream& operator<<(ostream& res, const Matrix<C> &a);
    template <typename C>
    friend Matrix<C> operator*(const C k, const Matrix<C> &a);
    int getRowsNumber() const;
    int getColumnsNumber()  const;
    Matrix operator-(const Matrix &) const;
    Matrix operator+(const Matrix &) const;
    Matrix operator*(const Matrix &) const;
    Matrix &operator=(const Matrix &);
    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator*=(const Matrix &);
    Matrix &operator*=(const T k);
    T operator()(int, int) const;
    Matrix operator*(const T k) const;
    Matrix operator/(const T k) const;
    Matrix getTransposed () const;
    Matrix &transpose ();
    
};
template <typename T>
void Matrix<T>::free_memory()
{
    for (int i = 0; i < this->row_count; i++)
        delete [] this->values[i];
    delete [] this->values;
}
template <typename T>
void Matrix<T>::set_memory(const int row_count, const int col_count)
{
    this->row_count = row_count;
    this->col_count = col_count;
    this->values = new T *[this->row_count];
    for (int i = 0; i < this->row_count; i++)
    {
        this->values[i] = new T[this->col_count];
    }
}
template <typename T>
void Matrix<T>::assign(const Matrix<T> &that)
{
    set_memory(that.row_count, that.col_count);
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->values[i][j] = that.values[i][j];
        }
    }
}
template <typename T>
Matrix<T>::Matrix()
{
}
template <typename T>
Matrix<T>::Matrix(const Matrix<T> &that)
{
    assign(that);
}
template <typename T>
Matrix<T>::Matrix(int row_count, int col_count)
{
    set_memory(row_count, col_count);
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < col_count; j++)
        {
            this->values[i][j] = 0;
        }
    }
}
template <typename T>
Matrix<T>::~Matrix() {
    free_memory();
}
template <typename T>
void Matrix<T>::set(int i, int j, T val)
{
    this->values[i][j] = val;
}
template <typename T>
T Matrix<T>::get(int i, int j) const
{
    return this->values[i][j];
}
template <typename T>
T Matrix<T>::operator()(int row, int column) const
{
    if (row >= this->row_count || column >= this->col_count) {
        throw MatrixIndexError();
    }
    return this->values[row][column];
}

template <typename C>
istream& operator>>(istream &in, const Matrix<C> &a)
{
    for (int i = 0; i < a.row_count; i++)
    {
        for (int j = 0; j < a.col_count; j++)
            in >> a.values[i][j];
    }
    return in;
}
template <typename C>
ostream& operator<<(ostream& res, const Matrix<C> &a)
{
    for (int i = 0; i < a.row_count; i++)
    {
        for (int j = 0; j < a.col_count; j++)
            res << a.values[i][j] << " ";
        res << endl;
    }
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &that) const
{
    if (this->row_count != that.row_count || this->col_count != that.col_count) {
        throw MatrixWrongSizeError();
    }
    Matrix res(this->row_count, this->col_count);
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            res.values[i][j] = this->values[i][j] + that.values[i][j];
        }
    }
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &that) const
{
    if (this->row_count != that.row_count || this->col_count != that.col_count) {
        throw MatrixWrongSizeError();
    }
    Matrix res(this->row_count, this->col_count);
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            res.values[i][j] = this->values[i][j] - that.values[i][j];
        }
    }
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &that) const
{
    if (this->col_count != that.row_count) {
        throw MatrixWrongSizeError();
    }
    Matrix res(this->row_count, that.col_count);
    for (int i = 0; i < res.row_count; i++)
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
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const T k) const
{
    Matrix res(this->row_count, this->col_count);
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            res.values[i][j] = this->values[i][j] * k;
        }
    }
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::operator/(const T k) const
{
    Matrix res(this->row_count, this->col_count);
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            res.values[i][j] = this->values[i][j] / k;
        }
    }
    return res;
}
template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &that)
{
    if (this != &that)
    {
        free_memory();
        assign(that);
    }
    return *this;
}
template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &that)
{
    *this = *this + that;
    return *this;
}
template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &that)
{
    *this = *this - that;
    return *this;
}
template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix &that)
{
    *this = *this * that;
    return *this;
}
template <typename T>
Matrix<T> &Matrix<T>::operator*=(const T k)
{
    *this = *this * k;
    return *this;
}
template <typename C>
Matrix<C> operator*(const C k, const Matrix<C> &a)
{
    return a * k;
}
template <typename T>
Matrix<T> Matrix<T>::getTransposed () const
{
    Matrix res(this->col_count, this->row_count);
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            res.values[j][i] = this->values[i][j];
        }
    }
    return res;
}
template <typename T>
Matrix<T> &Matrix<T>::transpose()
{
    *this = getTransposed();
    return *this;
}

template <typename T>
int Matrix<T>::getRowsNumber() const
{
    return this->row_count;
}
template <typename T>
int Matrix<T>::getColumnsNumber()  const
{
    return  this->col_count;
}

template <typename T>
void Matrix<T>::swap_rows(const int first, const int second) {
    for (int i = 0; i < this->col_count; i++)
    {
        T temp = this->values[first][i];
        this->values[first][i] = this->values[second][i];
        this->values[second][i] = -temp;
    }
}

template <typename T>
void Matrix<T>::row_sum_add(const int first_row, const int second_row, const T k) {
    for (int i = 0; i < this->col_count; i++) {
        this->set(first_row, i, this->values[first_row][i] + this->values[second_row][i] * k);
    }
}

#endif /* Matrix_hpp */
