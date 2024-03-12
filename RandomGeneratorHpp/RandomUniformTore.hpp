#include "RandomUniform.hpp"

class RandomUniformTore : public RandomUniform {
public:
	long prime;

	RandomUniformTore(long _prime);
	double computeValue() override;
};