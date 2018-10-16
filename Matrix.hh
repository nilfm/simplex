#ifndef _MATRIX_CLASS_
#define _MATRIX_CLASS_

#include "Includes.hh"
#include "Row.hh"

class Matrix{
private:
    vector<Row> matrix;
    
public:
    //Constructores
    Matrix(int size_i, int size_j);
    Matrix(int size_i, int size_j, double x);
    
    //Destructora
    ~Matrix();
    
    //Input-Output
    void input();
    void output() const;
    
    //Funcions basiques
    int size() const;
    void swap(int i, int j);
    
    //Funcions propies de les matrius
    Matrix transpose();
    double product_diagonal();
    double norm_1();
    double norm_inf(); 
    
    //Operadors
    Row& operator[](int x);
    Matrix operator+(Matrix& A);
    Matrix operator*(Matrix& A);
    Row operator*(Row& r);
    Matrix operator*(double d);
    Matrix operator-();
    Matrix operator-(Matrix& A);
    Matrix& operator=(Matrix A);
    Matrix& operator+=(Matrix A);
    Matrix& operator-=(Matrix A);
    Matrix& operator!(); //Transposicio - Altera el parametre implicit!!
};

//Altres operadors
Row operator*(double d, Row& r);
Matrix operator*(double d, Matrix& A);

#endif
