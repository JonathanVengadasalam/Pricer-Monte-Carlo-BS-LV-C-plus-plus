#ifndef DiffusionModel_HPP
#define DiffusionModel_HPP

class DiffusionModel {
public:
	double diffuseUnderlying(double spots[], double normals[], long iteration, long startInd, double dt);
	virtual double drift(double X_t, double _t) = 0;
	virtual double volatility(double X_t, double _t) = 0;
	virtual ~DiffusionModel() {}
};

#endif
