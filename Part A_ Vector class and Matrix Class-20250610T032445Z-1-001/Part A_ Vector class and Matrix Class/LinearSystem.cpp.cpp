#include "LinearSystem.h"
#include <cassert>
#include <cmath>

LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    assert(A.numRows() == A.numCols());
    assert(A.numRows() == b.size());

    mSize = A.numRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

// Gauss elimination with partial pivoting
Vector LinearSystem::Solve() {
    Matrix A = *mpA;
    Vector b = *mpb;

    for (int i = 1; i <= mSize; ++i) {
        // Pivoting
        int maxRow = i;
        double maxVal = std::abs(A(i, i));
        for (int k = i + 1; k <= mSize; ++k) {
            if (std::abs(A(k, i)) > maxVal) {
                maxVal = std::abs(A(k, i));
                maxRow = k;
            }
        }

        // Swap rows
        if (maxRow != i) {
            for (int j = 1; j <= mSize; ++j)
                std::swap(A(i, j), A(maxRow, j));
            std::swap(b(i), b(maxRow));
        }

        // Elimination
        for (int k = i + 1; k <= mSize; ++k) {
            double factor = A(k, i) / A(i, i);
            for (int j = i; j <= mSize; ++j)
                A(k, j) -= factor * A(i, j);
            b(k) -= factor * b(i);
        }
    }

    // Back substitution
    Vector x(mSize);
    for (int i = mSize; i >= 1; --i) {
        double sum = b(i);
        for (int j = i + 1; j <= mSize; ++j)
            sum -= A(i, j) * x(j);
        x(i) = sum / A(i, i);
    }

    return x;
}
