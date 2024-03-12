#include "DiffusionBlackScholes.hpp"
#include "RandomNormal.hpp"
#include "Utils.hpp"
#include <cmath>

DiffusionBlackScholes::DiffusionBlackScholes(double _mu, double _sigma) {
    mu = _mu;
    sigma = _sigma;
}

double DiffusionBlackScholes::drift(double X_t, double _t) {
    return X_t * mu;
}

double DiffusionBlackScholes::volatility(double X_t, double _t) {
    return X_t * sigma;
}

double DiffusionBlackScholes::logNormalFunction(double T, double normalMeasure_T) {
    return std::exp((mu - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * normalMeasure_T);
}

double DiffusionBlackScholes::reverseLogNormalFunction(double T, double spot_T) {
    return (std::log(spot_T) - ((mu - 0.5 * sigma * sigma) * T)) / (sigma * std::sqrt(T));
}

double d2(double S0, double K, double T, double mu, double sigma) {
    return (std::log(S0 / K) + (mu - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
}

// P[X_{T} < K]
double callableProba(double S0, double K, double T, double mu, double sigma) {
    return RandomNormal::Probability(d2(S0, K, T, mu, sigma));
}

// E[X_{T}, X_{T} < K]
double callableMean(double S0, double K, double T, double mu, double sigma) {
    return S0 * std::exp(mu * T) * RandomNormal::Probability(d2(S0, K, T, mu, sigma) + sigma * std::sqrt(T));
}

// E[X_{T} ** 2, X_{T} < K]
double callableMeanSquare(double S0, double K, double T, double mu, double sigma) {
    double proba = RandomNormal::Probability(d2(S0, K, T, mu, sigma) + 2 * sigma * std::sqrt(T));
    return S0 * S0 * std::exp((2 * mu + sigma * sigma) * T) * proba;
}

double DiffusionBlackScholes::europeanCallPayoffMean(double S0, double K, double T) {
    double mean = callableMean(S0, K, T, mu, sigma);
    double proba = callableProba(S0, K, T, mu, sigma);
    return std::exp(-mu * T) * (mean - proba * K);
}

double DiffusionBlackScholes::europeanCallPayoffVariance(double S0, double K, double T) {
    double mean = callableMean(S0, K, T, mu, sigma);
    double proba = callableProba(S0, K, T, mu, sigma);
    double meanSquare = callableMeanSquare(S0, K, T, mu, sigma);
    double payoffMeanSquare = std::exp(-2 * mu * T) * (meanSquare - 2 * K * mean + K * K * proba);
    double payoffMean = europeanCallPayoffMean(S0, K, T);
    return payoffMeanSquare - payoffMean * payoffMean;
}

