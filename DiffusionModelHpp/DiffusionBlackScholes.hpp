#include "DiffusionModel.hpp"

class DiffusionBlackScholes : public DiffusionModel {
public:
    double mu;
    double sigma;

    DiffusionBlackScholes(double _mu, double _sigma);
    double drift(double X_t, double _t) override;
    double volatility(double X_t, double _t) override;
    double logNormalFunction(double T, double normalMeasure_T);
    double reverseLogNormalFunction(double T, double spot_T);
    double europeanCallPayoffMean(double S0, double K, double T);
    double europeanCallPayoffVariance(double S0, double K, double T);
};