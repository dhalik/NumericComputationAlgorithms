#include <iostream>
#include <cstdlib>
#include <vector>
#include "polynomial.h"

using namespace std;

double LagrangeMonomial::eval(double x){
    double ret = 1;
    for (auto it = roots.begin(); it != roots.end(); it++)
        ret *= (x - *it);
    return ret / constant;
}

LagrangeMonomial::LagrangeMonomial(int pos, vector<int> _roots){
    constant = 1;
    xi = _roots[pos];
    for (auto it = _roots.begin(); it != _roots.end(); it++){
        if (it - _roots.begin() != pos){
            constant *= (xi - *it);
            roots.push_back(*it);
        }
    }
}

Polynomial::Polynomial(vector<int> x, vector<int> y){
    coeff = y;
    for (unsigned int it = 0; it < x.size(); it++){
        monads.push_back(new LagrangeMonomial(it, x));
    }
}

Polynomial::~Polynomial(){
    for (auto it = monads.begin(); it != monads.end(); it++)
        delete *it;
}

double Polynomial::eval(double x){
    double accum = 0;
    for (unsigned int i = 0; i < coeff.size(); i++)
        accum += coeff[i] * monads[i]->eval(x);
    return accum;
}
