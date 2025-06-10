#include "Vector.h"
#include <iostream>
using namespace std;

//Constructor
Vector::Vector(int size) {
    assert(size > 0);
    mSize = size;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = 0.0;
    }
   
}

//Copy constructor
Vector::Vector(const Vector& other) {
    mSize = other.mSize;
    mData = new double [mSize];
    for (int i = 0; i < mSize; ++i){
        mData[i] = other.mData[i];
    }
}

Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other){
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    return *this;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}
Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + other.mData[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - other.mData[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] * scalar;
    }
    return result;
}

// Vector - Vector
Vector operator-(const Vector& a, const Vector& b) {
    assert(a.size() == b.size());
    Vector result(a.size());
    for (int i = 0; i < a.size(); ++i)
        result[i] = a[i] - b[i];
    return result;
}

//dot product
double operator*(const Vector& a, const Vector& b) {
    assert(a.size() == b.size());
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i)
        sum += a[i] * b[i];
    return sum;
}


int Vector::size() const {
    return mSize;
}

void Vector::print() const {
    for (int i = 0; i < mSize; ++i) {
        std::cout << mData[i] << " ";
    }
    std::cout << std::endl;
}