#include "RandomNormalMoro.hpp"
#include <cmath>

RandomNormalMoro::RandomNormalMoro(RandomUniform &_uniform) : RandomNormal() {
	uniform = &_uniform;
}

void RandomNormalMoro::generateArray(double values[], long valuesLen) {
	uniform->generateArray(values, valuesLen);
	for (long i = 0; i < valuesLen; ++i) {
		values[i] = inverseNormalProba(values[i]);
	}
}

void RandomNormalMoro::initialize() {
	RandomNormal::initialize();
	uniform->initialize();
}

double RandomNormalMoro::computeValue() {
	return inverseNormalProba(uniform->generateValue());
}

double RandomNormalMoro::inverseNormalProba(double x) {
	double result;
	double y = x - 0.5;
	if (std::abs(y) < 0.42) {
		result = y * y;
		result = y *
			(((a3_ * result + a2_) * result + a1_) * result + a0_) /
		   ((((b3_ * result + b2_) * result + b1_) * result + b0_) * result + 1.0);
	}
	else {
		result = x < 0.5 ? x : 1. - x;
		result = std::log(-std::log(result));
		result = c0_ + result * (c1_ + result * (c2_ + result *
				(c3_ + result * (c4_ + result * (c5_ + result *
				(c6_ + result * (c7_ + result * c8_)))))));
		if (x < 0.5) result = -result;
	}
	return result;
}

const double RandomNormalMoro::a0_ = 2.50662823884;
const double RandomNormalMoro::a1_ = -18.61500062529;
const double RandomNormalMoro::a2_ = 41.39119773534;
const double RandomNormalMoro::a3_ = -25.44106049637;

const double RandomNormalMoro::b0_ = -8.47351093090;
const double RandomNormalMoro::b1_ = 23.08336743743;
const double RandomNormalMoro::b2_ = -21.06224101826;
const double RandomNormalMoro::b3_ = 3.13082909833;

const double RandomNormalMoro::c0_ = 0.3374754822726147;
const double RandomNormalMoro::c1_ = 0.9761690190917186;
const double RandomNormalMoro::c2_ = 0.1607979714918209;
const double RandomNormalMoro::c3_ = 0.0276438810333863;
const double RandomNormalMoro::c4_ = 0.0038405729373609;
const double RandomNormalMoro::c5_ = 0.0003951896511919;
const double RandomNormalMoro::c6_ = 0.0000321767881768;
const double RandomNormalMoro::c7_ = 0.0000002888167364;
const double RandomNormalMoro::c8_ = 0.0000003960315187;