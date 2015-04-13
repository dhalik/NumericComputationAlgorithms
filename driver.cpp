#include "matrix.h"
#include <iostream>
#include "rational.h"

using namespace std;

int main(){
    vector<Rational> v1, v2, v3;
    v1.push_back(Rational(2));
    v1.push_back(Rational(1));
    v1.push_back(Rational(4));
    v2.push_back(Rational(-4));
    v2.push_back(Rational(0));
    v2.push_back(Rational(6));
    v3.push_back(Rational(1));
    v3.push_back(Rational(1));
    v3.push_back(Rational(2));

    vector<vector<Rational> > mat;
    mat.push_back(v1);
    mat.push_back(v2);
    mat.push_back(v3);

    Matrix<Rational> m(mat);
    cout << *(m.lu()) << endl;
}
