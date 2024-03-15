#include "DiffusionModel.hpp"
#include <cmath>

double DiffusionModel::diffuseUnderlying(double spots[], double normals[], long iteration, long startInd, double dt) {
    spots[0] = 1.;
    double t = 0.;
    for (long i = 0; i < iteration; ++i) {
        double X_t = spots[i];
        spots[i + 1] = X_t + drift(X_t, t) * dt + volatility(X_t, t) * std::sqrt(dt) * normals[startInd + i];
        t += dt;
    }
    return spots[iteration];
}