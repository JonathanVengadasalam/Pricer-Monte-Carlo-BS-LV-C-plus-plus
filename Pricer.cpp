#include "Pricer.hpp"
#include "RandomUtils.hpp"
#include <cmath>

void MonteCarlo(double payoffs[], long payoffsLen, DiffusionModel& mod, EuropeanCall call, long timeSteps) {
	long N = std::ceil(252. * call.T / (double)timeSteps);
	for (long i = 0; i < payoffsLen; ++i) {
		double* spots = new double[N + 1];
		double* randoms = new double[N];

		normalDistritor(randoms, N);
		double X_T = mod.diffuseUnderlying(spots, N + 1, randoms, N, call.T / (double) N);
		payoffs[i] = call.payoffDiscounted(spots, N + 1, mod.drift(X_T, call.T));

		delete[] spots;
		delete[] randoms;
	}
}