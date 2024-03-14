#ifndef RandomUniform_HPP
#define RandomUniform_HPP

#include "RandomGenerator.hpp"

class RandomUniform : public RandomGenerator {
public:
	RandomUniform* shuffler;

	RandomUniform(long _N);
	RandomUniform(long _N, RandomUniform* _shuffler);
	double probability(double value) override;
	void generateArray(double values[], long valuesLen) override;
	void shuffle(double values[], long valuesLen);
};

#endif
