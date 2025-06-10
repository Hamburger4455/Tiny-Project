#include "PosSymLinSystem.h"
#include <cassert>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    // Kiểm tra đối xứng
    for (int i = 1; i <= mSize; ++i)
        for (int j = 1; j <= mSize; ++j)
            assert((*mpA)(i, j) == (*mpA)(j, i));
}

// Conjugate Gradient
Vector PosSymLinSystem::Solve() {
    Vector x(mSize);
    Vector r = *mpb - (*mpA) * x;
    Vector p = r;

    for (int k = 0; k < mSize; ++k) {
        Vector Ap = (*mpA) * p;
        double alpha = (r * r) / (p * Ap);
        x = x + p * alpha;
        Vector r_new = r - Ap * alpha;
        if (r_new * r_new < 1e-10)
            break;
        double beta = (r_new * r_new) / (r * r);
        p = r_new + p * beta;
        r = r_new;
    }

    return x;
}
