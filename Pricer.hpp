#include "DiffusionModel.hpp"
#include "EuropeanCall.hpp"
#include "RandomNormal.hpp"

void MonteCarlo(double prices[], long pricesLen, RandomNormal& generator, DiffusionModel& model, EuropeanCall call, long timeSteps);
