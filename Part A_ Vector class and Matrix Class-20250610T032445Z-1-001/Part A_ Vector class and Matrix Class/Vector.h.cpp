#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <iostream>

class Vector {
private:
    int mSize;
    double *mData;
public:
    Vector(int size);
    
    Vector (const Vector& other);
    
    ~Vector();
    
    Vector& operator = (const Vector& other) const;
    
    double& operator[](int index);
    
    double& operator()(int index);
    
    Vector operator+(const Vector& other) const;
    
    Vector operator-(const Vector& other) const;
    
    Vecotr operator*(double scalar) const;

    Vector operator-(const Vector& a, const Vector& b);

    double operator*(const Vector& a, const Vector& b);
    
    int size() const;
    
    void print() cons;
};

#

