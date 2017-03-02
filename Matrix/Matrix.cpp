//
//  Matrix.cpp
//  Matrix
//
//  Created by Alexey Karpov on 28.02.17.
//  Copyright © 2017 Alexey Karpov. All rights reserved.
//

#include "Matrix.hpp"
#include <cstring>

using namespace mipt;

int Matrix::count = 0;

Matrix::Matrix(const Matrix &old)
{
    this->raw_count = old.raw_count;
    this->col_count = old.col_count;
    this->values = new cell *[this->raw_count];
    for (int i = 0; i < this->raw_count; i++)
    {
        this->values[i] = new cell[this->col_count];
    }
    for (int i = 0; i < this->raw_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->values[i][j] = old.values[i][j];
        }
    }
    count++;
}
Matrix::Matrix(size_t raw_count, size_t col_count):
    raw_count(raw_count), col_count(col_count)
{
    this->values = new cell *[this->raw_count];
    for (int i = 0; i < this->raw_count; i++)
    {
        this->values[i] = new cell[this->col_count];
    }
    count++;
}
Matrix::~Matrix() {
    for (int i = 0; i < this->raw_count; i++)
        delete [] this->values[i];
    delete [] this->values;
}
void Matrix::set(size_t i, size_t j, cell val)
{
    this->values[i][j] = val;
}
cell Matrix::get(size_t i, size_t j) const
{
    return this->values[i][j];
}
namespace mipt {
    istream& operator>>(istream &in, const Matrix &a)
    {
        for (int i = 0; i < a.raw_count; i++)
        {
            for (int j = 0; j < a.col_count; j++)
                in >> a.values[i][j];
        }
        return in;
    }
    ostream& operator<<(ostream& res, const Matrix &a)
    {
        for (int i = 0; i < a.raw_count; i++)
        {
            for (int j = 0; j < a.col_count; j++)
                res << a.values[i][j] << " ";
            res << endl;
        }
        return res;
    }
    Matrix operator*(const int k, const Matrix &a) {
        Matrix res(a.raw_count, a.col_count);
        for (int i = 0; i < a.raw_count; i++)
        {
            for (int j = 0; j < a.col_count; j++)
            {
                res.values[i][j] = a.values[i][j] * k;
            }
        }
        return res;
    }
}
Matrix Matrix::operator+(const Matrix &that)
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
Matrix Matrix::operator*(const Matrix &that)
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
Matrix Matrix::operator*(const int k)
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
