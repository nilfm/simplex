#ifndef _MATRIX_CLASS_
#define _MATRIX_CLASS_

#include "Includes.hh"
#include "Row.hh"

class Matrix{
private:
    vector<Row> matrix;
    
public:
    //Constructores
    Matrix();
    Matrix(int size_i, int size_j);
    Matrix(int size_i, int size_j, long double x);
    static Matrix identitat(int n);
    
    //Destructora
    ~Matrix();
    
    //Input-Output
    void input();
    void output() const;
    
    //Funcions basiques
    int size() const;
    void pop_back();
    void push_back(Row& r);
    void swap(int i, int j);
    Row columna(int j);                     //Retorna la jesima columna del p.i.
    void modificar_columna(int j, Row& c);  //La jesima columna del p.i. passa a ser c
    void modificar_columna(int j, Row c);   //overloading sense referencia - fa el mateix
    
    //Funcions propies de les matrius
    Matrix transpose();
    long double product_diagonal();
    long double norm_1();
    long double norm_inf(); 
    void gauss();
    
    //Operadors
    Row& operator[](int x);
    Matrix operator+(Matrix A);
    Matrix operator*(Matrix A);
    Row operator*(Row r);
    Matrix operator*(long double d);
    Matrix operator-();
    Matrix operator-(Matrix A);
    Matrix& operator=(Matrix A);
    Matrix& operator+=(Matrix A);
    Matrix& operator-=(Matrix A);
    Matrix& operator!(); //Transposicio - Altera el parametre implicit!!
};

//Altres operadors
Matrix operator*(long double d, Matrix A);
Row operator*(Row b, Matrix A);

#endif
