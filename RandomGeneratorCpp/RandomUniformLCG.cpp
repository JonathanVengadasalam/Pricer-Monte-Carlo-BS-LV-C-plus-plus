#include "RandomUniformLCG.hpp"
#include <cmath>

RandomUniformLCG::RandomUniformLCG(size_t _x) : RandomUniform(0) {
	x = _x;
}

double RandomUniformLCG::computeValue() {
	x = (a_ * x + c_) % m_;
	return x / (double) m_;
}

const size_t RandomUniformLCG::a_ = 16807;
const size_t RandomUniformLCG::c_ = 0;
const size_t RandomUniformLCG::m_ = (size_t) std::pow(2, 31) - 1;