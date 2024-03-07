#include "DiffusionModel.hpp"

class DiffusionDupire : public DiffusionModel {
public:
    double mu;
    double* sigma;
    double* x;
    double* t;
    long xLen;
    long tLen;

    DiffusionDupire(double _mu, double _sigma[], double _x[], long _xLen, double _t[], long _tLen);
    double drift(double X_t, double _t) override;
    double volatility(double X_t, double _t) override;
};