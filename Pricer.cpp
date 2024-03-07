#include "Pricer.hpp"
#include "Utils.hpp"
#include <cmath>
#include <random>

void MonteCarlo(double payoffs[], long payoffsLen, DiffusionModel& mod, EuropeanCall call, long timeSteps) {
	long N = std::ceil(252. * call.T / (double)timeSteps);
	double dt = call.T / (double)N;
	for (long i = 0; i < payoffsLen; ++i) {
		double* spots = new double[N + 1];
		double* randoms = new double[N];

		normalDistritor(randoms, N);
		double X_T = mod.diffuseUnderlying(spots, N + 1, randoms, N, dt);
		payoffs[i] = call.payoffDiscounted(spots, N + 1, mod.drift(X_T, call.T));

		delete[] spots;
		delete[] randoms;
	}
}