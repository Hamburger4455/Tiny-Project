#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>
using namespace std;

class LinearRegression {
private:
    vector<float> weights;  // model parameters
    float bias;             // intercept
    float learningRate;     // learning rate
    int epochs;             // number of epochs

public:
    LinearRegression();                    // default constructor
    LinearRegression(float lr, int ep);   // constructor with parameters

    void fit(const vector<vector<float>>& X, const vector<float>& y);
    float predict(const vector<float>& x) const;
    vector<float> predict(const vector<vector<float>>& X) const;
};

#endif
