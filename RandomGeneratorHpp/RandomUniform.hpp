#ifndef RandomUniform_HPP
#define RandomUniform_HPP

#include "RandomGenerator.hpp"

class RandomUniform : public RandomGenerator {
public:
	RandomUniform* shuffler;

	RandomUniform();
	RandomUniform(RandomUniform* _shuffler);
	void initialize() override;
	double probability(double value) override;
	void generateArray(double values[], long valuesLen) override;
	void shuffle(double values[], long valuesLen);
};

#endif