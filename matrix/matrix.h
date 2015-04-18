#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <vector>
#include <iostream>
#include "rational.h"

template<class T>

class Matrix{
    int rows;
    int cols;
    bool isLU;
    std::vector<std::vector<T>*> * values;

    //subtract two std::vectors
    std::vector<T> sub(std::vector<T> a, std::vector<T> b){
        for (auto it = a.begin(); it != a.end(); it++)
            *it - b[it - a.begin()];
        return a;
    }

    //scale a given std::vector by s
    void scale(T s, std::vector<T>& a){
        for (auto it = a.begin(); it != a.end(); it++)
            *it *= s;
    }

    T dot(std::vector<T> a, std::vector<T> b){
        T total =0 ;
        for (int i = 0; i < a.size(); i++)
            total += a[i] * b[i];
        return total;
    }

    public:
        Matrix(int cols, int rows):cols(cols), rows(rows){
            isLU = false;
            values = new std::vector<std::vector<T>* >();
            for (int i = 0; i < rows; i++){
                std::vector<T>* curr = new std::vector<T>();
                for (int j = 0; j < cols; j++)
                    curr->push_back(0);
                values->push_back(curr);
            }
        }

        Matrix(const std::vector<std::vector<T> > & _values){
            this->rows= _values.size();
            this->cols = _values[0].size();
            isLU = false;
            values = new std::vector<std::vector<T>* >();
            for (int i = 0; i < rows; i++){
                std::vector<T>* curr = new std::vector<T>();
                for (int j = 0; j < cols; j++)
                    curr->push_back(_values[i][j]);
                values->push_back(curr);
            }
        }

        Matrix(const Matrix<T>& m){
            isLU = false;
            values = new std::vector<std::vector<T> * >();
            for (int i = 0; i < m.rowSize(); i++){
                std::vector<T> * row = m.getRow(i);
                values->push_back(row);
            }
        }

        ~Matrix(){
            for (int i = 0; i < rows; i++)
                delete (*values)[i];
            delete values;
        }

        std::vector<T>* getCol(int m) const{
            std::vector<T> * ret = new std::vector<T>();
            for (int i = 0; i < rows; i++)
                ret->push_back((*(*values)[i])[m]);
            return ret;
        }

        std::vector<T>* getRow(int m) const{
            std::vector<T> * ret = new std::vector<T>();
            for (int i = 0; i < cols; i++){
                ret->push_back((*(*values)[m])[i]);
            }
            return ret;
        }

        int colSize() const{
            return cols;
        }

        int rowSize() const{
            return rows;
        }

        void set(int row, int col, T val){
            (*(*values)[row])[col] = val;
        }

        T get(int row, int col){
            return (*(*values)[row])[col];
        }

        // TODO still need to complete pivots

        Matrix<T>* lu(){
            std::vector<std::vector<T> > newMat;
            std::vector<std::vector<T>* > col;
            for (int j = 0; j < this->rowSize(); j++){
                std::vector<T> * col = this->getRow(j);
                newMat.push_back(*col);
                delete col;
            }

            for (unsigned int i = 0; i < newMat.begin()->size(); i++){
                // i is the current pivot
                T pivot = newMat[i][i];
                for (unsigned int row = i + 1; row < newMat.size(); row++){
                    newMat[row][i] = newMat[row][i] / pivot;
                    //adjust row value for pivot value change
                    for (unsigned int col = i + 1; col < newMat.begin()->size(); col++){
                        newMat[row][col] = newMat[row][col] - newMat[i][col] * newMat[row][i];
                    }
                }
            }
            Matrix<T> * m = new Matrix<T>(newMat);
            m->isLU = true;
            return m;
        }

        Matrix<T>* inverse(){

        }

        Matrix<T>* transpose(){
            std::vector<std::vector<T> > newMat;
            for (int j = 0; j < this->colSize(); j++){
                std::vector<T> * col = this->getCol(j);
                newMat.push_back(*col);
                delete col;
            }
            return new Matrix<T>(newMat);
        }


        Matrix<T>* mult(const Matrix<T>& B){
            int rowSize = this->rowSize();
            int colSize = B.colSize();

            std::vector<std::vector<T> > newMat;
            for (int i = 0; i < rowSize; i++){
                std::vector<T> first = std::vector<T>();

                for (int j = 0; j < colSize; j++){
                    std::vector<T> * col = B.getCol(j);
                    std::vector<T> * row = getRow(i);
                    first.push_back(dot(*col,*row));
                    delete col;
                    delete row;
                }
                newMat.push_back(first);
            }

            return new Matrix<T>(newMat);
        }

        Matrix<T>* add(Matrix<T> B){
            std::vector<std::vector<T> > newMat;
            for (int i = 0; i < rows; i++){
                std::vector<T> first = std::vector<T>();
                for (int j = 0; j < cols; j++){
                    first.push_back(get(i,j) + B.get(i,j));
                }
                newMat.push_back(first);
            }
            return new Matrix<T>(newMat);
        }

        T determinant(){

        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<U> & m);
        template <class X> friend class Matrix;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T> & m){
        for (int i = 0; i < m.rows; i++){
            for (int j = 0; j < m.cols; j++){
                out << (*(*(m.values))[i])[j] << "\t";
            }
            out << std::endl;
        }
        if (m.isLU)
            out << "In LU Form";
        return out;
}
#endif
