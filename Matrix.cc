#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"

// Constructors, Destructors
Matrix::Matrix() {}

Matrix::Matrix(int size_i, int size_j) {
    matrix = vector<Row>(size_i, Row(size_j));
}

Matrix::Matrix(int size_i, int size_j, long double x) {
    matrix = vector<Row>(size_i, Row(size_j, x));
}

Matrix::~Matrix() {}


// Operadors
Row& Matrix::operator[](int x) {
    return matrix[x];
}

Matrix Matrix::operator+(Matrix A) {
    Matrix add(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) add[i] = matrix[i] + A[i];
    return add;
}

Matrix Matrix::operator*(Matrix A) {
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

Row Matrix::operator*(Row r) {
    Row s(matrix.size());
    for (int i = 0; i < size(); ++i) s[i] = matrix[i]*r;
    return s;
}

Matrix Matrix::operator*(long double d) {
    Matrix B(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) B[i] = matrix[i]*d;
    return B;
}

Matrix operator*(long double d, Matrix A) {
    return A*d;
}

Matrix Matrix::operator-() {
    Matrix B(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) B[i] = -matrix[i];
    return B;
}

Matrix Matrix::operator-(Matrix A) {
    Matrix add(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) add[i] = matrix[i] - A[i];
    return add;
}

Matrix& Matrix::operator=(Matrix A) {
    this->matrix = A.matrix;
    return *this;
}

Matrix& Matrix::operator+=(Matrix A) {
    return *this = *this + A;
}

Matrix& Matrix::operator-=(Matrix A) {
    return *this = *this - A;
}

Matrix& Matrix::operator!() {
    for (int i = 0; i < size(); i++) {
        for (int j = i+1; j < matrix[i].size(); j++) {
            long double temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    return *this;
}

// Input-Output
void Matrix::input() {
    for (int i = 0; i < size(); i++) matrix[i].input();
}

void Matrix::output() const {
    for (int i = 0; i < this->size(); i++){
        matrix[i].output();
    }
}

// Funcions basiques
int Matrix::size() const {
    return matrix.size();
}

void Matrix::swap(int i, int j) {
    Row t = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = t;
}

Row Matrix::columna(int j) {
    Row c(size());
    for (int i = 0; i < size(); i++) {
        c[i] = matrix[i][j];
    }
    return c;
}

void Matrix::modificar_columna(int j, Row& c) {
    for (int i = 0; i < size(); i++) {
        matrix[i][j] = c[i];
    }
}

void Matrix::modificar_columna(int j, Row c) {
    for (int i = 0; i < size(); i++) {
        matrix[i][j] = c[i];
    }
}

// Funcions propies de les matrius
long double Matrix::product_diagonal() {
    long double prod = 1;
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

long double Matrix::norm_1() {
    int a = size();
    int b = matrix[0].size();
    long double max = 0;
    for (int j = 0; j < b; j++){
        long double sum = 0;
        for (int i = 0; i < a; i++){
            sum += matrix[i][j];
        }
        if (sum > max) max = sum;
    }
    return max;
}

long double Matrix::norm_inf() {
    int a = size();
    int b = matrix[0].size();
    long double max = 0;
    for (int i = 0; i < a; i++){
        long double sum = 0;
        for (int j = 0; j < b; j++){
            sum += matrix[i][j];
        }
        if (sum > max) max = sum;
    }
    return max;
}

Row operator*(Row b, Matrix A) {
    int m = A[0].size();
    Row r(m);
    for (int i = 0; i < m; ++i) r[i] = b*A.columna(i);
    return r;
}

