#include "RandomUniformTore.hpp"
#include <cmath>

RandomUniformTore::RandomUniformTore(long _prime) : RandomUniform(0) {
	prime = _prime;
}

double RandomUniformTore::computeValue() {
	return N * std::sqrt(prime) - std::floor(N * std::sqrt(prime));
}

