#include "RandomGenerator.hpp"
#include <cmath>

RandomGenerator::RandomGenerator(long _N) {
	N = _N;
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

long RandomGenerator::kolmogorovSmirnovInd(double ascendingValues[], long ascendingValuesLen) {
    long maxDistanceInd = -1;
    double maxDistance = 0.;
    double empiricLen = (double)ascendingValuesLen;
    for (long i = 0; i < ascendingValuesLen; ++i) {
        double scaleDistance = std::abs(probability(ascendingValues[i]) - (i + 1) / empiricLen);
        if (scaleDistance > maxDistance) {
            maxDistance = scaleDistance;
            maxDistanceInd = i;
        }
    }
    return maxDistanceInd;
}
