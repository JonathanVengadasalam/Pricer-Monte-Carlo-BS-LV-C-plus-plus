#include "BlackScholes.hpp"
#include "RandomUtils.hpp"
#include <cmath>

BlackScholes::BlackScholes(double _mu, double _sigma) {
    mu = _mu;
    sigma = _sigma;
}

double BlackScholes::drift(double X_t, double t) {
    return X_t * mu;
}

double BlackScholes::volatility(double X_t, double t) {
    return X_t * sigma;
}

double BlackScholes::logNormalFunction(double T, double normalMeasure_T) {
    return std::exp((mu - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * normalMeasure_T);
}

double BlackScholes::reverseLogNormalFunction(double T, double spot_T) {
    return (std::log(spot_T) - ((mu - 0.5 * sigma * sigma) * T)) / (sigma * std::sqrt(T));
}

double d2(double S0, double K, double T, double mu, double sigma) {
    return (std::log(S0 / K) + (mu - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
}

// P[X_{T} < K]
double callableProba(double S0, double K, double T, double mu, double sigma) {
    return normalProba(d2(S0, K, T, mu, sigma));
}

// E[X_{T}, X_{T} < K]
double callableMean(double S0, double K, double T, double mu, double sigma) {
    return S0 * std::exp(mu * T) * normalProba(d2(S0, K, T, mu, sigma) + sigma * std::sqrt(T));
}

// E[X_{T} ** 2, X_{T} < K]
double callableMeanSquare(double S0, double K, double T, double mu, double sigma) {
    double proba = normalProba(d2(S0, K, T, mu, sigma) + 2 * sigma * std::sqrt(T));
    return S0 * S0 * std::exp((2 * mu + sigma * sigma) * T) * proba;
}

double BlackScholes::europeanCallPayoffMean(double S0, double K, double T) {
    double mean = callableMean(S0, K, T, mu, sigma);
    double proba = callableProba(S0, K, T, mu, sigma);
    return std::exp(-mu * T) * (mean - proba * K);
}

double BlackScholes::europeanCallPayoffVariance(double S0, double K, double T) {
    double mean = callableMean(S0, K, T, mu, sigma);
    double proba = callableProba(S0, K, T, mu, sigma);
    double meanSquare = callableMeanSquare(S0, K, T, mu, sigma);
    double payoffMeanSquare = std::exp(-2 * mu * T) * (meanSquare - 2 * K * mean + K * K * proba);
    double payoffMean = europeanCallPayoffMean(S0, K, T);
    return payoffMeanSquare - payoffMean * payoffMean;
}

