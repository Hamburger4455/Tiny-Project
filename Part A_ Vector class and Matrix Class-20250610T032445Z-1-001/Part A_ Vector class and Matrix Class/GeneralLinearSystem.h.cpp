#ifndef GENERALLINEARSYSTEM_H
#define GENERALLINEARSYSTEM_H

#include "Matrix.h"
#include "Vector.h"

class GeneralLinearSystem {
private:
    Matrix A;
    Vector b;

public:
    GeneralLinearSystem(const Matrix& A_, const Vector& b_);

    Vector SolveByPseudoInverse();
    Vector SolveByTikhonov(double lambda);
};

#endif
