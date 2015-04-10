#include "matrix.h"
#include <iostream>

using namespace std;

// construct a matrix of size m = cols x n = rows
Matrix::Matrix(int cols, int rows):cols(cols), rows(rows){
    isLU = false;
    values = new vector<vector<double>* >();
    for (int i = 0; i < rows; i++){
        vector<double>* curr = new vector<double>();
        for (int j = 0; j < cols; j++)
            curr->push_back(0);
        values->push_back(curr);
    }
}

Matrix::Matrix(const vector<vector<double> > & _values){
    this->rows= _values.size();
    this->cols = _values[0].size();
    isLU = false;
    values = new vector<vector<double>* >();
    for (int i = 0; i < rows; i++){
        vector<double>* curr = new vector<double>();
        for (int j = 0; j < cols; j++)
            curr->push_back(_values[i][j]);
        values->push_back(curr);
    }
}

Matrix::Matrix(const Matrix& m){
    isLU = false;
    values = new vector<vector<double> * >();
    for (int i = 0; i < m.rowSize(); i++){
        vector<double> * row = m.getRow(i);
        values->push_back(row);
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < rows; i++)
        delete (*values)[i];
    delete values;
}

vector<double>* Matrix::getCol(int m) const{
    vector<double> * ret = new vector<double>();
    for (int i = 0; i < rows; i++)
        ret->push_back((*(*values)[i])[m]);
    return ret;
}

vector<double>* Matrix::getRow(int m) const{
    vector<double> * ret = new vector<double>();
    for (int i = 0; i < cols; i++){
        ret->push_back((*(*values)[m])[i]);
    }
    return ret;
}

int Matrix::colSize() const{
    return cols;
}

int Matrix::rowSize() const{
    return rows;
}

void Matrix::set(int row, int col, double val){
    (*(*values)[row])[col] = val;
}

double Matrix::get(int row, int col){
    return (*(*values)[row])[col];
}

//subtract two vectors
vector<double> sub(vector<double> a, vector<double> b){
    for (auto it = a.begin(); it != a.end(); it++)
        *it - b[it - a.begin()];
    return a;
}

//scale a given vector by s
void scale(double s, vector<double>& a){
    for (auto it = a.begin(); it != a.end(); it++)
        *it *= s;
}

Matrix* Matrix::lu(){
    vector<vector<double > > newMat;
    vector<vector<double >* > col;
    for (int j = 0; j < this->rowSize(); j++){
        vector<double> * col = this->getRow(j);
        newMat.push_back(*col);
        delete col;
    }

    for (int i = 0; i < newMat.begin()->size(); i++){
        // i is the current pivot
        double pivot = newMat[i][i];
        for (int row = i + 1; row < newMat.size(); row++){
            newMat[row][i] = newMat[row][i] / pivot;
            //adjust row value for pivot value change
            for (int col = i + 1; col < newMat.begin()->size(); col++){
                newMat[row][col] = newMat[row][col] - newMat[i][col] * newMat[row][i];
            }
        }
    }
    Matrix * m = new Matrix(newMat);
    m->isLU = true;
    return m;
}

Matrix* Matrix::inverse(){

}

Matrix* Matrix::transpose(){
    vector<vector<double> > newMat;
    for (int j = 0; j < this->colSize(); j++){
        vector<double> * col = this->getCol(j);
        newMat.push_back(*col);
        delete col;
    }
    return new Matrix(newMat);
}

int dot(vector<double> a, vector<double> b){
    int total =0 ;
    for (int i = 0; i < a.size(); i++)
        total += a[i] * b[i];
    return total;
}

Matrix* Matrix::mult(const Matrix& B){
    int rowSize = this->rowSize();
    int colSize = B.colSize();

    vector<vector<double > > newMat;
    for (int i = 0; i < rowSize; i++){
        vector<double> first = vector<double>();

        for (int j = 0; j < colSize; j++){
            vector<double> * col = B.getCol(j);
            vector<double> * row = getRow(i);
            first.push_back(dot(*col,*row));
            delete col;
            delete row;
        }
        newMat.push_back(first);
    }

    return new Matrix(newMat);
}

Matrix* Matrix::add(Matrix B){
    vector<vector<double> > newMat;
    for (int i = 0; i < rows; i++){
        vector<double> first = vector<double>();
        for (int j = 0; j < cols; j++){
            first.push_back(get(i,j) + B.get(i,j));
        }
        newMat.push_back(first);
    }
    return new Matrix(newMat);
}

double Matrix::determinant(){

}

ostream& operator<<(ostream& out, const Matrix & m){
    for (int i = 0; i < m.rows; i++){
        for (int j = 0; j < m.cols; j++){
            out << (*(*(m.values))[i])[j] << "\t";
        }
        out << endl;
    }
    if (m.isLU)
        cout << "In LU Form";
    return out;
}
