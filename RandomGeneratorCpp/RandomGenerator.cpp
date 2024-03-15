#include "RandomGenerator.hpp"
#include <cmath>

RandomGenerator::RandomGenerator() {
	N = 0;
}

double RandomGenerator::generateValue() {
	++N;
	return computeValue();
}

void RandomGenerator::computeArray(double values[], long valuesLen) {
    for (long i = 0; i < valuesLen; ++i) {
        values[i] = generateValue();
    }
}

void RandomGenerator::kolmogorovSmirnov(double values[], long valuesLen, double ascendingValues[]) {
    double empiricLen = (double)valuesLen;
    for (long i = 0; i < valuesLen; ++i) {
        values[i] = std::abs(probability(ascendingValues[i]) - (i + 1) / empiricLen);
    }
}

void RandomGenerator::initialize() {
    N = 0;
}