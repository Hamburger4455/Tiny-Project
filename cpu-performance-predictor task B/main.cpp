#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "LinearRegression.h"

using namespace std;

// Function to read the dataset
void readCSV(const string& filename, vector<vector<float>>& X, vector<float>& y) {
    ifstream file(filename);
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        stringstream ss(line);
        string token;
        vector<float> row;

        // Skip vendor and model name
        getline(ss, token, ',');
        getline(ss, token, ',');

        // Read the next 6 features
        bool valid = true;
        for (int i = 0; i < 6; ++i) {
            if (!getline(ss, token, ',')) {
                valid = false;
                break;
            }
            try {
                row.push_back(stof(token));
            } catch (...) {
                valid = false;
                break;
            }
        }

        // Read the label (PRP)
        if (valid && getline(ss, token, ',')) {
            try {
                float value = stof(token);
                y.push_back(value);
                X.push_back(row);
            } catch (...) {
                cerr << "Invalid PRP at line " << lineNum << endl;
            }
        } else {
            cerr << "Skipping malformed line " << lineNum << ": " << line << endl;
        }
    }
}

// Function to split dataset
void splitData(const vector<vector<float>>& X, const vector<float>& y,
               vector<vector<float>>& X_train, vector<float>& y_train,
               vector<vector<float>>& X_test, vector<float>& y_test) {
    size_t total = X.size();
    size_t train_size = static_cast<size_t>(total * 0.8);

    for (size_t i = 0; i < total; ++i) {
        if (i < train_size) {
            X_train.push_back(X[i]);
            y_train.push_back(y[i]);
        } else {
            X_test.push_back(X[i]);
            y_test.push_back(y[i]);
        }
    }
}

// Compute mean and std for each feature column
void computeMeanStd(const vector<vector<float>>& X, vector<float>& means, vector<float>& stds) {
    int n_features = X[0].size();
    int n_samples = X.size();
    means.resize(n_features, 0.0f);
    stds.resize(n_features, 0.0f);

    // Compute means
    for (int j = 0; j < n_features; ++j) {
        float sum = 0.0f;
        for (int i = 0; i < n_samples; ++i) {
            sum += X[i][j];
        }
        means[j] = sum / n_samples;
    }

    // Compute std deviations
    for (int j = 0; j < n_features; ++j) {
        float sq_sum = 0.0f;
        for (int i = 0; i < n_samples; ++i) {
            float diff = X[i][j] - means[j];
            sq_sum += diff * diff;
        }
        stds[j] = sqrt(sq_sum / n_samples);
        if (stds[j] == 0.0f) stds[j] = 1.0f;  // avoid division by zero
    }
}

// Normalize dataset inplace
void normalizeFeatures(vector<vector<float>>& X, const vector<float>& means, const vector<float>& stds) {
    int n_features = X[0].size();
    int n_samples = X.size();
    for (int i = 0; i < n_samples; ++i) {
        for (int j = 0; j < n_features; ++j) {
            X[i][j] = (X[i][j] - means[j]) / stds[j];
        }
    }
}


int main() {
    vector<vector<float>> X, X_train, X_test;
    vector<float> y, y_train, y_test;

    readCSV("machine.data", X, y);
    cout << "Total samples loaded: " << X.size() << endl;

    if (X.empty() || y.empty()) {
        cerr << "Error: No valid data loaded." << endl;
        return 1;
    }

    // Normalize all features BEFORE split
    vector<float> means, stds;
    computeMeanStd(X, means, stds);
    normalizeFeatures(X, means, stds);

    splitData(X, y, X_train, y_train, X_test, y_test);
    cout << "Training samples: " << X_train.size() << ", Test samples: " << X_test.size() << endl;

    LinearRegression model(1e-6f, 1000);
    model.fit(X_train, y_train);

    float mse = 0.0f;
    for (size_t i = 0; i < X_test.size(); ++i) {
        float pred = model.predict(X_test[i]);
        if (std::isnan(pred)) {
            cout << "NaN prediction at index " << i << endl;
            cout << "Input: ";
            for (auto f : X_test[i]) cout << f << " ";
            cout << endl;
        }
        float err = pred - y_test[i];
        mse += err * err;
    }

    mse /= X_test.size();
    float rmse = sqrt(mse);

    cout << "RMSE on test data: " << rmse << endl;

    return 0;
}
