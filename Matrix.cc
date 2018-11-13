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

Matrix Matrix::operator*(double d) {
    Matrix B(matrix.size(), matrix[0].size());
    for (int i = 0; i < size(); i++) B[i] = matrix[i]*d;
    return B;
}

Matrix operator*(double d, Matrix A) {
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
            double temp = matrix[i][j];
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

double Matrix::norm_inf() {
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

//retorna 0 si det A == 0
int Matrix::LU(Row& perm) {
    int n = size();
    for (int i = 0; i < n; ++i) perm[i] = i;
    for (int i = 0; i < n; ++i) {
        int b = 0;
        double value = 0;
        for (int j = i; j < n; ++j) {
            double cur = 1;
            for (int k = i; k < n; ++k) {
                if (abs(matrix[j][i]/matrix[j][k]) < cur) cur = abs(matrix[j][i]/matrix[j][k]);
            }
            if (cur > value) value = cur, b = j;
        }
        this->swap(b, i);
        swap(perm[b], perm[i]);
        if (abs(matrix[i][i]) < TOLERANCIA){
            return 0;
        }
        for (int j = i + 1; j < n; ++j) {
            matrix[j][i] /= matrix[i][i];
            for (int k = i + 1; k < n; ++k) matrix[j][k] -= matrix[j][i]*matrix[i][k];
        }
    }
    if (abs(matrix[n-1][n-1]) < TOLERANCIA) return 0;
    return 1;
}

Row Matrix::solve_upper_triangular(Row& b){
    int n = size();
    Row x(n);
    for (int i = n - 1; i >= 0; --i){
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j){
            x[i] = x[i] - matrix[i][j]*x[j];
        }
        x[i] /= matrix[i][i];
    }
    return x;
}

Row Matrix::solve_lower_triangular(Row& b){
    int n = size();
    Row x(n);
    for (int i = 0; i < n; ++i){
        x[i] = b[i];
        for (int j = 0; j < i; ++j){
            x[i] = x[i] - matrix[i][j]*x[j];
        }
        //x[i] /= matrix[i][i]; el deixo comentat pero en LU la lower te A[i][i] = 1 per tot i, aixi que no cal
    }
    return x;
}

Row Matrix::resol(Row& b, Row& perm){
    Row c = b.permute(perm);
    Row y = solve_lower_triangular(c);
    return solve_upper_triangular(y);
}

//yes tested
//retorna matriu de mida 0 si la inversa no existeix
Matrix Matrix::inverse() {
    int n = size();
    Row perm(n);
    Matrix copy = *this;
    if (copy.LU(perm) == 0) return Matrix(0, 0);
    Matrix inv(n, n);
    for (int i = 0; i < n; ++i) {
        Row b(n, 0);
        b[i] = 1;
        inv[i] = copy.resol(b, perm);
    }
    return inv.transpose();
}

Row operator*(Row b, Matrix A) {
    int m = A[0].size();
    Row r(m);
    for (int i = 0; i < m; ++i) r[i] = b*A.columna(i);
    return r;
}

