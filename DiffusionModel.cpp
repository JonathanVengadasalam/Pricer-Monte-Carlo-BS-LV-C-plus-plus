#include "DiffusionModel.hpp"
#include <cmath>

double DiffusionModel::diffuseUnderlying(double spots[], long spotsLen, double normals[], long normalsLen, double dt) {
    spots[0] = 1.;
    double t = 0.;
    for (long i = 0; i < normalsLen; ++i) {
        t += dt;
        double X_t = spots[i];
        spots[i + 1] = X_t + drift(X_t, t) * dt + volatility(X_t, t) * std::sqrt(dt) * normals[i];
    }
    return spots[spotsLen - 1];
}