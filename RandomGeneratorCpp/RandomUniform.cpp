#include "RandomUniform.hpp"
#include <cmath>

RandomUniform::RandomUniform(long _N) : RandomGenerator(_N) {
	shuffler = nullptr;
}

RandomUniform::RandomUniform(long _N, RandomUniform* _shuffler) : RandomGenerator(_N) {
	shuffler = _shuffler;
}

double RandomUniform::probability(double value) {
	return value;
}

void RandomUniform::generateArray(double values[], long valuesLen) {
	computeArray(values, valuesLen);
	if (shuffler != nullptr) {
		shuffler->shuffle(values, valuesLen);
	}
}

void RandomUniform::shuffle(double values[], long valuesLen) {
	for (long i = 0; i < valuesLen; ++i) {
		long ind = std::floor(generateValue() * valuesLen);
		double tmp = values[i];
		values[i] = values[ind];
		values[ind] = tmp;
	}
}
