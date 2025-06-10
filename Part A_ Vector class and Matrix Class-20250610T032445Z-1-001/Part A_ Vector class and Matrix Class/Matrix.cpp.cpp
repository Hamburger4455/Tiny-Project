#include "Matrix.h"
#include <cassert>
#include <cmath>
#include <stdexcept>

Matrix::Matrix(int rows, int cols) : mNumRows(rows), mNumCols(cols) {
    mData = new double*[rows];
    for (int i = 0; i < rows; i++) {
        mData[i] = new double[cols]();
    }
}

Matrix::Matrix(const Matrix& other)
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other(i+1, j+1);
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; i++) delete[] mData[i];
    delete[] mData;
}

int Matrix::GetNumRows() const { return mNumRows; }
int Matrix::GetNumCols() const { return mNumCols; }

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

double Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

Matrix& Matrix::operator=(const Matrix& A) {
    if (this != &A) {
        if (mNumRows != A.mNumRows || mNumCols != A.mNumCols) {
            for (int i = 0; i < mNumRows; i++) delete[] mData[i];
            delete[] mData;

            mNumRows = A.mNumRows;
            mNumCols = A.mNumCols;
            mData = new double*[mNumRows];
            for (int i = 0; i < mNumRows; i++) {
                mData[i] = new double[mNumCols];
            }
        }
        for (int i = 0; i < mNumRows; i++)
            for (int j = 0; j < mNumCols; j++)
                mData[i][j] = A(i+1, j+1);
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& A) const {
    assert(mNumRows == A.mNumRows && mNumCols == A.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; i++)
        for (int j = 1; j <= mNumCols; j++)
            result(i, j) = (*this)(i, j) + A(i, j);
    return result;
}

Matrix Matrix::operator-(const Matrix& A) const {
    assert(mNumRows == A.mNumRows && mNumCols == A.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; i++)
        for (int j = 1; j <= mNumCols; j++)
            result(i, j) = (*this)(i, j) - A(i, j);
    return result;
}

Matrix Matrix::operator*(const Matrix& A) const {
    assert(mNumCols == A.mNumRows);
    Matrix result(mNumRows, A.mNumCols);
    for (int i = 1; i <= mNumRows; i++)
        for (int j = 1; j <= A.mNumCols; j++)
            for (int k = 1; k <= mNumCols; k++)
                result(i, j) += (*this)(i, k) * A(k, j);
    return result;
}

Vector Matrix::operator*(const Vector& v) const {
    assert(mNumCols == v.Size());
    Vector result(mNumRows);
    for (int i = 1; i <= mNumRows; i++)
        for (int j = 1; j <= mNumCols; j++)
            result(i) += (*this)(i, j) * v(j);
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; i++)
        for (int j = 1; j <= mNumCols; j++)
            result(i, j) = (*this)(i, j) * scalar;
    return result;
}

Matrix operator*(double scalar, const Matrix& A) {
    return A * scalar;
}

Matrix Matrix::Transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; i++)
        for (int j = 1; j <= mNumCols; j++)
            result(j, i) = (*this)(i, j);
    return result;
}

Matrix Matrix::Inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix A(*this);
    Matrix I(n, n);
    for (int i = 1; i <= n; i++) I(i, i) = 1.0;

    for (int i = 1; i <= n; i++) {

        double maxEl = std::abs(A(i, i));
        int maxRow = i;
        for (int k = i + 1; k <= n; k++) {
            if (std::abs(A(k, i)) > maxEl) {
                maxEl = std::abs(A(k, i));
                maxRow = k;
            }
        }


        for (int k = 1; k <= n; k++) {
            std::swap(A(i, k), A(maxRow, k));
            std::swap(I(i, k), I(maxRow, k));
        }


        double diag = A(i, i);
        assert(std::abs(diag) > 1e-12); // Kiểm tra không chia cho 0
        for (int k = 1; k <= n; k++) {
            A(i, k) /= diag;
            I(i, k) /= diag;
        }


        for (int j = 1; j <= n; j++) {
            if (j == i) continue;
            double factor = A(j, i);
            for (int k = 1; k <= n; k++) {
                A(j, k) -= factor * A(i, k);
                I(j, k) -= factor * I(i, k);
            }
        }
    }

    return I;
}
double Matrix::Determinant() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix A(*this);
    double det = 1.0;

    for (int i = 1; i <= n; ++i) {

        double maxEl = std::abs(A(i, i));
        int maxRow = i;
        for (int k = i + 1; k <= n; ++k) {
            if (std::abs(A(k, i)) > maxEl) {
                maxEl = std::abs(A(k, i));
                maxRow = k;
            }
        }


        if (std::abs(maxEl) < 1e-12)
            return 0.0;


        if (maxRow != i) {
            for (int j = 1; j <= n; ++j)
                std::swap(A(i, j), A(maxRow, j));
            det *= -1;  // đổi dòng đổi dấu định thức
        }

        det *= A(i, i);

        for (int k = i + 1; k <= n; ++k) {
            double factor = A(k, i) / A(i, i);
            for (int j = i; j <= n; ++j)
                A(k, j) -= factor * A(i, j);
        }
    }

    return det;
}





