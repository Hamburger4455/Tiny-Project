#include "LinearRegression.h"
#include <numeric>  // for inner_product
#include <cmath>    // for pow
#include <algorithm> // for fill
using namespace std;

LinearRegression::LinearRegression() : learningRate(0.00000001f), epochs(1000), bias(0.0f) {}

LinearRegression::LinearRegression(float lr, int ep) : learningRate(lr), epochs(ep), bias(0.0f) {}

void LinearRegression::fit(const vector<vector<float>>& X, const vector<float>& y) {
    int n_samples = X.size();
    int n_features = X[0].size();

    weights.resize(n_features, 0.0f);
    vector<float> gradients(n_features, 0.0f);
    float bias_gradient = 0.0f;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        fill(gradients.begin(), gradients.end(), 0.0f);
        bias_gradient = 0.0f;

        for (int i = 0; i < n_samples; ++i) {
            float prediction = bias;
            for (int j = 0; j < n_features; ++j) {
                prediction += weights[j] * X[i][j];
            }
            float error = prediction - y[i];
            for (int j = 0; j < n_features; ++j) {
                gradients[j] += error * X[i][j];
            }
            bias_gradient += error;
        }

        for (int j = 0; j < n_features; ++j) {
            weights[j] -= learningRate * gradients[j] / n_samples;
        }
        bias -= learningRate * bias_gradient / n_samples;
    }
}

float LinearRegression::predict(const vector<float>& x) const {
    float result = bias;
    for (size_t i = 0; i < x.size(); ++i) {
        result += weights[i] * x[i];
    }
    return result;
}

vector<float> LinearRegression::predict(const vector<vector<float>>& X) const {
    vector<float> predictions;
    for (const auto& row : X) {
        predictions.push_back(predict(row));
    }
    return predictions;
}
