#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <vector>
#include <iostream>

class Matrix{
    int rows;
    int cols;
    std::vector<std::vector<double>*> * values;

    public:
        // construct a matrix of size m x n, initialized to 0
        Matrix(int m, int n);

        // construct a matrix with a 2d vector reference, copying the input struct
        Matrix(const Matrix&);
        Matrix(const std::vector<std::vector<double> > &);
        ~Matrix();

        // get columns and rows. Returns a heap allocated copy
        std::vector<double>* getCol(int) const;
        std::vector<double>* getRow(int) const;
        int colSize() const;
        int rowSize() const;

        // set row i, column j to val
        void set(int i, int j, double val);

        // element access
        double get (int i, int j);

        //Matrix operations
        M
            trix* rref() const;
        Matrix* inverse();
        Matrix* transpose();
        Matrix* mult(const Matrix&);
        Matrix* add(Matrix B);
        double determinant();

        //Matrix output
        friend std::ostream & operator<<(std::ostream&, const Matrix &);
};

#endif
