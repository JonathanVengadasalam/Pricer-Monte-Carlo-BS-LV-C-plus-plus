#include "DiffusionModel.hpp"

class BlackScholes : public DiffusionModel {
public:
    double mu;
    double sigma;

    BlackScholes(double _mu, double _sigma);
    double drift(double X_t, double t) override;
    double volatility(double X_t, double t) override;
    double logNormalFunction(double T, double normalMeasure_T);
    double reverseLogNormalFunction(double T, double spot_T);
    double europeanCallPayoffMean(double S0, double K, double T);
    double europeanCallPayoffVariance(double S0, double K, double T);
};