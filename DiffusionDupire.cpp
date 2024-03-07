#include "DiffusionDupire.hpp"
#include "Utils.hpp"

DiffusionDupire::DiffusionDupire(double _mu, double _sigma[], double _x[], long _xLen, double _t[], long _tLen) {
    mu = _mu; sigma = _sigma;
    x = _x; xLen = _xLen;
    t = _t; tLen = _tLen;
}

double DiffusionDupire::drift(double X_t, double t) {
    return X_t * mu;
}

double DiffusionDupire::volatility(double X_t, double _t) {
    long xInd = firstInfIndex(x, xLen, X_t);
    long tInd = firstInfIndex(t, tLen, _t);
    double x0 = x[xInd];
    double t0 = t[tInd];
    double x1 = x[xInd + 1];
    double t1 = t[tInd + 1];

    return X_t * (
           sigma[x0 + tLen * t0] * (x1 - X_t) * (t1 - _t)
         + sigma[x1 + tLen * t0] * (x0 - X_t) * (t1 - _t)
         + sigma[x0 + tLen * t1] * (x1 - X_t) * (t0 - _t)
         + sigma[x1 + tLen * t1] * (x0 - X_t) * (t0 - _t));
}
