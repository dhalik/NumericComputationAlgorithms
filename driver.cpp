#include "matrix.h"
#include <iostream>

using namespace std;

Matrix getM1(){
    vector<double> v1, v2;
    v1.push_back(1.1);
    v1.push_back(2.2);
    v1.push_back(3);
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);
    vector<vector<double> > mat;
    mat.push_back(v1);
    mat.push_back(v2);
    Matrix m = Matrix(mat);
    return m;
}

Matrix getM2(){
    vector<double> v1, v2, v3;
    v1.push_back(1);
    v1.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v3.push_back(5);
    v3.push_back(6);

    vector<vector<double> > mat;

    mat.push_back(v1);
    mat.push_back(v2);
    mat.push_back(v3);

    Matrix m = Matrix(mat);
    return m;
}

int main(){
    Matrix m = getM1();
    cout << m << endl;
    cout << *m.add(m) << endl;
}
