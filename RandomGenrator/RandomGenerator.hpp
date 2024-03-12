#ifndef RandomGenerator_HPP
#define RandomGenerator_HPP

class RandomGenerator {
public:
	long N;

	RandomGenerator(long _N);
	double generateValue();
	void computeArray(double values[], long valuesLen);
	long kolmogorovSmirnovInd(double ascendingValues[], long ascendingValuesLen);

	virtual double computeValue() = 0;
	virtual double probability(double value) = 0;
	virtual void generateArray(double values[], long valuesLen) = 0;
	virtual ~RandomGenerator() {}
};

#endif
