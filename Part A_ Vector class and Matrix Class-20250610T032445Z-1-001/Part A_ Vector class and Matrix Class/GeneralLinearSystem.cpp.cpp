#include "GeneralLinearSystem.h"
#include <cassert>

GeneralLinearSystem::GeneralLinearSystem(const Matrix& A_, const Vector& b_)
    : A(A_), b(b_) {
    assert(A.GetNumRows() == b.Size());
}

Vector GeneralLinearSystem::SolveByPseudoInverse() {
    Matrix At = A.Transpose();
    Matrix AtA = At * A;
    Matrix AtA_inv = AtA.Inverse();
    Matrix pseudoInv = AtA_inv * At;
    return pseudoInv * b;
}

Vector GeneralLinearSystem::SolveByTikhonov(double lambda) {
    int n = A.GetNumCols();
    Matrix At = A.Transpose();
    Matrix I(n, n);
    for (int i = 1; i <= n; ++i) I(i, i) = 1.0;

    Matrix regularized = (At * A) + lambda * I;
    Matrix regInv = regularized.Inverse();
    Matrix solution = regInv * At;
    return solution * b;
}
