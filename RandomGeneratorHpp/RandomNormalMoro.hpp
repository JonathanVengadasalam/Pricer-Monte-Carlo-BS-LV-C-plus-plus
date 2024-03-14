#include "RandomUniform.hpp"
#include "RandomNormal.hpp"

class RandomNormalMoro : public RandomNormal {
public:
    RandomUniform *uniform;
    RandomUniform *shuffler;

    RandomNormalMoro(RandomUniform &_uniform, RandomUniform *_shuffler);
    double computeValue() override;
    void generateArray(double values[], long valuesLen) override;
    static double inverseNormalProba(double x);

private:
    static const double a0_;
    static const double a1_;
    static const double a2_;
    static const double a3_;

    static const double b0_;
    static const double b1_;
    static const double b2_;
    static const double b3_;

    static const double c0_;
    static const double c1_;
    static const double c2_;
    static const double c3_;
    static const double c4_;
    static const double c5_;
    static const double c6_;
    static const double c7_;
    static const double c8_;
};
