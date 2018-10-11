#include "Includes.hh"
#include "Row.hh"

// Constructors, Destructors
Row::Row(int size) {
    this->row = vector<double>(size);
}

Row::Row(int size, double x){
    this->row = vector<double>(size, x);
}

Row::~Row() {}


// Operadors

double& Row::operator[](int x){
    return row[x];
}

Row Row::operator+(Row &r) {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = r[i] + row[i];
    return s;
}

double Row::operator*(Row &r) {
    double s = 0;
    for (int i = 0; i < size(); i++) s += r[i]*row[i];
    return s;
}

Row Row::operator*(double d) {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = row[i]*d;
    return s;
}

Row operator*(double d, Row& r) {
    return r*d;
}

Row Row::operator-() {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = -row[i];
    return s;
}

Row Row::operator-(Row& r) {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = r[i] - row[i];
    return s;
}

Row& Row::operator=(Row r) {
    this->row = r.row;
    return *this;
}


// Input, Output

void Row::input() {
    for (int i = 0; i < size(); i++) cin >> row[i];
}

void Row::output() {
    for (int i = 0; i < size(); i++){
        cout << setw(PADDING) << row[i];
    }
    cout << endl;
}

void Row::output_vertical() {
    for (int i = 0; i < size(); i++){
        cout << setw(PADDING) << row[i] << endl;
    }
}


// Funcions basiques

int Row::size() {
    return row.size();
}


// Funcions propies dels vectors

double Row::norm_1() {
    double suma = 0;
    for (int i = 0; i < size(); i++) suma += abs(row[i]);
    return suma;
}

double Row::norm_2() {
    double suma = 0;
    for (int i = 0; i < size(); i++) suma += row[i]*row[i];
    return sqrt(suma);
}

double Row::norm_p(double p) {
    double suma = 0;
    for (int i = 0; i < size(); i++) suma += pow(abs(row[i]), p);
    return pow(suma, 1/p);
}

double Row::norm_inf() {
    double max = 0;
    for (int i = 0; i < size(); i++){
        if (abs(row[i]) > max) max = abs(row[i]); 
    }
    return max;
}
