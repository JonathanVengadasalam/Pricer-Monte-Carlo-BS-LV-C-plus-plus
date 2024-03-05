#include "EuropeanCall.hpp"
#include <cmath>

EuropeanCall::EuropeanCall(double _K, double _T) {
	K = _K;
	T = _T;
}

double EuropeanCall::payoffDiscounted(double spots[], long spotsLen, double rate) {
	return std::exp(- rate * T) * std::fmax(0., spots[spotsLen - 1] - K);
}
