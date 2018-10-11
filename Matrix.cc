#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"


Matrix::Matrix(int size_i, int size_j) {
    this->matrix = (Row*)calloc(size_i, sizeof(Row));
    for (int i = 0; i < size_i; i++){
        matrix[i] = Row(size_j);
    }
    rows = size_i;
}

Matrix::Matrix(int size_i, int size_j, double x) {
    this->matrix = (Row*)calloc(size_i, sizeof(Row));
    for (int i = 0; i < size_i; i++){
        matrix[i] = Row(size_j, x);
    }
    rows = size_i;
}

Matrix::~Matrix() {}

Row& Matrix::operator[](int x){
    return matrix[x];
}

Matrix Matrix::operator+(Matrix& A){
    Matrix add(this->size(), 0);
    for (int i = 0; i < this->size(); i++) add[i] = this->matrix[i] + A[i];
    return add;
}

Matrix Matrix::operator*(Matrix& A){
    Matrix B = A.transpose();
    int a = this->size();
    int b = B.size();
    Matrix prod(a, b);
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            prod[i][j] = this->matrix[i]*B[j];
        }
    }
    return prod;
}

Row Matrix::operator*(Row& r) {
    int a = this->size();
    Row s(a);
    for (int i = 0; i < a; ++i) s[i] = this->matrix[i]*r;
    return s;
}

Matrix Matrix::operator*(double d) {
    Matrix B(this->size(), 0);
    for (int i = 0; i < this->size(); i++) B[i] = this->matrix[i]*d;
    return B;
}

Matrix operator*(double d, Matrix& A) {
    return A*d;
}

Matrix Matrix::operator-() {
    Matrix B(this->size(), 0);
    for (int i = 0; i < this->size(); i++) B[i] = -this->matrix[i];
    return B;
}

Matrix Matrix::operator-(Matrix A) {
    Matrix add(this->size(), 0);
    for (int i = 0; i < this->size(); i++) add[i] = this->matrix[i] - A[i];
    return add;
}

int Matrix::size() {
    return rows;
}

void Matrix::swap(int i, int j) {
    Row t = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = t;
}

void Matrix::input() {
    for (int i = 0; i < rows; i++) matrix[i].input();
}

void Matrix::output() {
    for (int i = 0; i < this->size(); i++){
        this->matrix[i].output();
    }
}

void Matrix::copy(Matrix& A){
    for (int i = 0; i < this->size(); i++){
        matrix[i].copy(A[i]);
    } 
}

double Matrix::product_diagonal() {
    double prod = 1;
    int size = this->size();
    for (int i = 0; i < size; i++){
        prod *= this->matrix[i][i];
    }
    return prod;
}

Matrix Matrix::transpose() {
    Matrix T(this->matrix[0].size(), this->size());
    for (int i = 0; i < this->size(); ++i) {
        for (int j = 0; j < this->matrix[i].size(); ++j) {
            T[j][i] = this->matrix[i][j];
        }
    }
    return T;
}

double Matrix::norm_1() {
    int a = this->size();
    int b = this->matrix[0].size();
    double max = 0;
    for (int j = 0; j < b; j++){
        double sum = 0;
        for (int i = 0; i < a; i++){
            sum += this->matrix[i][j];
        }
        if (sum > max) max = sum;
    }
    return max;
}

double Matrix::norm_inf(){
    int a = this->size();
    int b = this->matrix[0].size();
    double max = 0;
    for (int i = 0; i < a; i++){
        double sum = 0;
        for (int j = 0; j < b; j++){
            sum += this->matrix[i][j];
        }
        if (sum > max) max = sum;
    }
    return max;
}




