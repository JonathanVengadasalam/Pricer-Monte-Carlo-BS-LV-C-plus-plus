#include "RandomUniform.hpp"

class RandomUniformLCG : public RandomUniform {
public:
    size_t x;

    RandomUniformLCG(size_t _x);
    double computeValue() override;

private:
    static const size_t a_;
    static const size_t c_;
    static const size_t m_;
};