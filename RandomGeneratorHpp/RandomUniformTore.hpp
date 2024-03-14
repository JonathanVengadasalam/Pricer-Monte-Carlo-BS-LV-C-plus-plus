#include "RandomUniform.hpp"

class RandomUniformTore : public RandomUniform {
public:
	long prime;

	RandomUniformTore(long _prime);
	RandomUniformTore(long _prime, RandomUniform* _shuffler);
	double computeValue() override;
};
