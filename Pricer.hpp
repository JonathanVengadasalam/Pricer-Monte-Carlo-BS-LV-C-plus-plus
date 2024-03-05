#include "DiffusionModel.hpp"
#include "EuropeanCall.hpp"

void MonteCarlo(double prices[], long pricesLen, DiffusionModel &mod, EuropeanCall call, long timeSteps);
