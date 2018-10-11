#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"

// Constructors, Destructors

Matrix::Matrix(int size_i, int size_j) {
    matrix = vector<Row>(size_i, Row(size_j));
}

Matrix::Matrix(int size_i, int size_j, double x) {
    matrix = vector<Row>(size_i, Row(size_j, x));
}

Matrix::~Matrix() {}


// Operadors

Row& Matrix::operator[](int x) {
    return matrix[x];
}

Matrix Matrix::operator+(Matrix& A) {
    Matrix add(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) add[i] = matrix[i] + A[i];
    return add;
}

Matrix Matrix::operator*(Matrix& A) {
    Matrix B = A.transpose();
    int a = matrix.size();
    int b = B.size();
    Matrix prod(a, b);
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            prod[i][j] = matrix[i]*B[j];
        }
    }
    return prod;
}

Row Matrix::operator*(Row& r) {
    Row s(matrix.size());
    for (int i = 0; i < size(); ++i) s[i] = matrix[i]*r;
    return s;
}

Matrix Matrix::operator*(double d) {
    Matrix B(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) B[i] = matrix[i]*d;
    return B;
}

Matrix operator*(double d, Matrix& A) {
    return A*d;
}

Matrix Matrix::operator-() {
    Matrix B(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) B[i] = -matrix[i];
    return B;
}

Matrix Matrix::operator-(Matrix& A) {
    Matrix add(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) add[i] = matrix[i] - A[i];
    return add;
}

Matrix& Matrix::operator=(Matrix A) {
    this->matrix = A.matrix;
    return *this;
}


// Funcions basiques

int Matrix::size() {
    return matrix.size();
}

void Matrix::swap(int i, int j) {
    Row t = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = t;
}

void Matrix::input() {
    for (int i = 0; i < size(); i++) matrix[i].input();
}

void Matrix::output() {
    for (int i = 0; i < this->size(); i++){
        matrix[i].output();
    }
}


// Funcions propies de les matrius

double Matrix::product_diagonal() {
    double prod = 1;
    for (int i = 0; i < size(); i++){
        prod *= matrix[i][i];
    }
    return prod;
}

Matrix Matrix::transpose() {
    Matrix T(matrix[0].size(), size());
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            T[j][i] = matrix[i][j];
        }
    }
    return T;
}

double Matrix::norm_1() {
    int a = size();
    int b = matrix[0].size();
    double max = 0;
    for (int j = 0; j < b; j++){
        double sum = 0;
        for (int i = 0; i < a; i++){
            sum += matrix[i][j];
        }
        if (sum > max) max = sum;
    }
    return max;
}

double Matrix::norm_inf(){
    int a = size();
    int b = matrix[0].size();
    double max = 0;
    for (int i = 0; i < a; i++){
        double sum = 0;
        for (int j = 0; j < b; j++){
            sum += matrix[i][j];
        }
        if (sum > max) max = sum;
    }
    return max;
}




