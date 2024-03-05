class EuropeanCall {
public:
	double K;
	double T;

	EuropeanCall(double _K, double _T);
	double payoffDiscounted(double spots[], long spotsLen, double rate);
};