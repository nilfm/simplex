#include "Includes.hh"
#include "Row.hh"

// Constructors, Destructors
Row::Row() {}

Row::Row(int size) {
    this->row = vector<long double>(size);
}

Row::Row(int size, long double x){
    this->row = vector<long double>(size, x);
}

Row::~Row() {}


// Operadors

long double& Row::operator[](int x){
    return row[x];
}

Row Row::operator+(Row r) {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = r[i] + row[i];
    return s;
}

long double Row::operator*(Row r) {
    long double s = 0;
    for (int i = 0; i < size(); i++) s += r[i]*row[i];
    return s;
}

Row Row::operator*(long double d) {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = row[i]*d;
    return s;
}

Row operator*(long double d, Row r) {
    return r*d;
}

Row Row::operator-() {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = -row[i];
    return s;
}

Row Row::operator-(Row r) {
    Row s(size());
    for (int i = 0; i < size(); i++) s[i] = row[i] - r[i];
    return s;
}

Row& Row::operator=(Row r) {
    this->row = r.row;
    return *this;
}

Row& Row::operator+=(Row r) {
    return *this = *this + r;
}

Row& Row::operator-=(Row r) {
    return *this = *this - r;
}

bool Row::operator>=(Row b) {
    for (int i = 0; i < size(); i++) if (row[i] < b[i]) return false;
    return true;
}

bool Row::operator>(Row b) {
    for (int i = 0; i < size(); i++) if (row[i] <= b[i]) return false;
    return true;
}

bool Row::operator<(Row b) {
    for (int i = 0; i < size(); i++) if (row[i] >= b[i]) return false;
    return true;
}

bool Row::operator<=(Row b) {
    for (int i = 0; i < size(); i++) if (row[i] > b[i]) return false;
    return true;
}


// Input, Output

void Row::input() {
    for (int i = 0; i < size(); i++) cin >> row[i];
}

void Row::output() const {
    for (int i = 0; i < size(); i++){
        cout << setw(PADDING) << row[i];
    }
    cout << endl;
}

void Row::output_vertical() const {
    for (int i = 0; i < size(); i++){
        cout << setw(PADDING) << row[i] << endl;
    }
}


// Funcions basiques

int Row::size() const {
    return row.size();
}

void Row::pop_back() {
    row.pop_back();
}

void Row::push_back(long double r) {
    row.push_back(r);
}

Row Row::permute(Row& perm){
    Row res(size());
    for (int i = 0; i < size(); ++i) {
        res[i] = row[perm[i]];
    }
    return res;
}


// Funcions propies dels vectors

long double Row::norm_1() const {
    long double suma = 0;
    for (int i = 0; i < size(); i++) suma += abs(row[i]);
    return suma;
}

long double Row::norm_2() const {
    long double suma = 0;
    for (int i = 0; i < size(); i++) suma += row[i]*row[i];
    return sqrt(suma);
}

long double Row::norm_p(long double p) const {
    long double suma = 0;
    for (int i = 0; i < size(); i++) suma += pow(abs(row[i]), p);
    return pow(suma, 1/p);
}

long double Row::norm_inf() const {
    long double max = 0;
    for (int i = 0; i < size(); i++){
        if (abs(row[i]) > max) max = abs(row[i]); 
    }
    return max;
}
