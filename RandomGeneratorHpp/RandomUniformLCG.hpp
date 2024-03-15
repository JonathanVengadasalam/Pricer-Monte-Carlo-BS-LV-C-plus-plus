#include "RandomUniform.hpp"

class RandomUniformLCG : public RandomUniform {
public:
    size_t x;
    size_t x0;

    RandomUniformLCG(size_t _x);
    void initialize() override;
    double computeValue() override;

private:
    static const size_t a_;
    static const size_t c_;
    static const size_t m_;
};