#include "RandomUniform.hpp"
#include <cmath>

RandomUniform::RandomUniform() : RandomGenerator() {
	shuffler = nullptr;
}

RandomUniform::RandomUniform(RandomUniform* _shuffler) : RandomGenerator() {
	shuffler = _shuffler;
}

void RandomUniform::initialize() {
	RandomGenerator::initialize();
	if (shuffler != nullptr) {
		shuffler->initialize();
	}
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