#include "RandomNormal.hpp"
#include <cmath>

RandomNormal::RandomNormal() : RandomGenerator() {}

double RandomNormal::Probability(double value) {
	return 0.5 * (1 + std::erf(value / std::sqrt(2.0)));
}

double RandomNormal::probability(double value) {
    return Probability(value);
}

double RandomNormal::andersonDarling(double ascendingValues[], long ascendingValuesLen) {
    double somme = 0.;
    for (long i = 1; i < ascendingValuesLen + 1; ++i) {
        somme += (2 * i - 1) * (std::log(Probability(ascendingValues[i - 1])) 
                              + std::log(1 - Probability(ascendingValues[ascendingValuesLen - i])));
    }
    return -(double)ascendingValuesLen - somme / ascendingValuesLen;
}