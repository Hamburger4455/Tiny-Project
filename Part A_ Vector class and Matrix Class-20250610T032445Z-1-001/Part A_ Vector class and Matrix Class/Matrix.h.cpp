#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();

    int GetNumRows() const;
    int GetNumCols() const;

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    Matrix& operator=(const Matrix& A);
    Matrix operator+(const Matrix& A) const;
    Matrix operator-(const Matrix& A) const;
    Matrix operator*(const Matrix& A) const;
    Vector operator*(const Vector& v) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& A);

    Matrix Transpose() const;
    Matrix Inverse() const;
    double Determinant() const; // optional


};