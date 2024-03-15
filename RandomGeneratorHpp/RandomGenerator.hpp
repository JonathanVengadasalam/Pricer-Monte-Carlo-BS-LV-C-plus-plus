#ifndef RandomGenerator_HPP
#define RandomGenerator_HPP

class RandomGenerator {
public:
	long N;

	RandomGenerator();
	double generateValue();
	void computeArray(double values[], long valuesLen);
	void kolmogorovSmirnov(double values[], long valuesLen, double ascendingValues[]);

	virtual void initialize();
	virtual double computeValue() = 0;
	virtual double probability(double value) = 0;
	virtual void generateArray(double values[], long valuesLen) = 0;
	virtual ~RandomGenerator() {}
};

#endif