#include "RandomUniformTore.hpp"
#include <cmath>

RandomUniformTore::RandomUniformTore(long _prime) : RandomUniform() {
	prime = _prime;
}

RandomUniformTore::RandomUniformTore(long _prime, RandomUniform* _shuffler) : RandomUniform(_shuffler) {
	prime = _prime;
}

double RandomUniformTore::computeValue() {
	return N * std::sqrt(prime) - std::floor(N * std::sqrt(prime));
}

