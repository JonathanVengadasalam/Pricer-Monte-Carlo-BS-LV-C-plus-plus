#include "Pricer.hpp"
#include <cmath>

void MonteCarlo(double payoffs[], long payoffsLen, RandomNormal& generator, DiffusionModel& model, EuropeanCall call, long timeSteps) {
	long N = std::ceil(252. * call.T / (double)timeSteps);
	double dt = call.T / (double)N;
	long randomsLen = N * payoffsLen;
	double* randoms = new double[randomsLen];
	double* spots = new double[N + 1];

	generator.generateArray(randoms, randomsLen);
	for (long i = 0; i < payoffsLen; ++i) {
		double X_T = model.diffuseUnderlying(spots, randoms, N, i * N, dt);
		payoffs[i] = call.payoffDiscounted(spots, N + 1, model.drift(X_T, call.T));
	}
	delete[] randoms;
	delete[] spots;
}
