#include "Includes.hh"
#include "Row.hh"

Row::Row(int size) {
    this->row = (double*)calloc(size, sizeof(double));
    this->cols = size;
}

Row::Row(int size, double x){
    this->row = (double*)calloc(size, sizeof(double));
    this->cols = size;
    for (int i = 0; i < size; i++){
        this->row[i] = x;
    }
}
Row::~Row() {}


double& Row::operator[](int x){
    return row[x];
}

Row Row::operator+(Row &r) {
    Row s(this->size());
    for (int i = 0; i < this->size(); i++) s[i] = r[i] + this->row[i];
    return s;
}

double Row::operator*(Row &r) {
    double s = 0;
    for (int i = 0; i < this->size(); i++) s += r[i]*this->row[i];
    return s;
}

Row Row::operator*(double d) {
    Row s(this->size());
    for (int i = 0; i < this->size(); i++) s[i] = this->row[i]*d;
    return s;
}

Row operator*(double d, Row& r) {
    return r*d;
}

Row Row::operator-() {
    Row s(this->size());
    for (int i = 0; i < this->size(); i++) s[i] = -this->row[i];
    return s;
}

int Row::size() {
    return cols;
}

Row Row::operator-(Row& r) {
    Row s(this->size());
    for (int i = 0; i < this->size(); i++) s[i] = r[i] - this->row[i];
    return s;
}

void Row::copy(Row& r){
    for (int i = 0; i < this->size(); i++){
        r[i] = row[i];
    }
}

void Row::input() {
    for (int i = 0; i < cols; i++) cin >> row[i];
}

void Row::output() {
    for (int i = 0; i < this->size(); i++){
        cout << setw(PADDING) << this->row[i];
    }
    cout << endl;
}

void Row::output_vertical() {
    for (int i = 0; i < this->size(); i++){
        cout << setw(PADDING) << this->row[i] << endl;
    }
}

double Row::norm_1() {
    int size = this->size();
    double suma = 0;
    for (int i = 0; i < size; i++) suma += abs(this->row[i]);
    return suma;
}

double Row::norm_2() {
    int size = this->size();
    double suma = 0;
    for (int i = 0; i < size; i++) suma += this->row[i]*this->row[i];
    return sqrt(suma);
}

double Row::norm_p(double p) {
    int size = this->size();
    double suma = 0;
    for (int i = 0; i < size; i++) suma += pow(abs(this->row[i]), p);
    return pow(suma, 1/p);
}

double Row::norm_inf() {
    int size = this->size();
    double max = 0;
    for (int i = 0; i < size; i++){
        if (abs(this->row[i]) > max) max = abs(this->row[i]); 
    }
    return max;
}
