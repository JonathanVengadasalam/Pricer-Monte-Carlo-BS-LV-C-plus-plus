#ifndef RandomNormal_HPP
#define RandomNormal_HPP

#include "RandomGenerator.hpp"

class RandomNormal : public RandomGenerator {
public:
	RandomNormal();
	double probability(double value) override;
	double andersonDarling(double ascendingValues[], long ascendingValuesLen);
	static double Probability(double value);
};

#endif