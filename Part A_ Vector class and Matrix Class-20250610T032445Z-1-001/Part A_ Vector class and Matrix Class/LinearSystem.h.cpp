#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();

    virtual Vector Solve();  // Gaussian Elimination
};

#endif