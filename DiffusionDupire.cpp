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
    long xInd0 = firstInfIndex(x, xLen, X_t);
    long tInd0 = firstInfIndex(t, tLen, _t);
    long xInd1 = xInd0 + 1;
    long tInd1 = tInd0 + 1;
    double x0 = x[xInd0];
    double t0 = t[tInd0];
    double x1 = x[xInd1];
    double t1 = t[tInd1];

    return X_t * (
           sigma[xInd0 + tLen * tInd0] * (x1 - X_t) * (t1 - _t)
         + sigma[xInd1 + tLen * tInd0] * (x0 - X_t) * (t1 - _t)
         + sigma[xInd0 + tLen * tInd1] * (x1 - X_t) * (t0 - _t)
         + sigma[xInd1 + tLen * tInd1] * (x0 - X_t) * (t0 - _t));
}
