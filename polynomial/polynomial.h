#ifndef __POLYNOMIAL__H__

#define __POLYNOMIAL__H__

#include <vector>

class LagrangeMonomial{
        std::vector<int> roots;
        int xi;
        int constant;
    public:
        LagrangeMonomial(int, std::vector<int>);
        double eval(double);
};

class Polynomial{
        std::vector<int> coeff;
        std::vector<LagrangeMonomial*> monads;
    public:
        double eval(double);
        Polynomial(std::vector<int>, std::vector<int>);
        ~Polynomial();
};

#endif
