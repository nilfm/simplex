#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"

int main() {
    Matrix M(3, 3, 3.14);
    Matrix A(3, 3);
    A.input();
    
    M += (M += A);
    M.output();
    cout << "------------------" << endl;
    (!M).output();
    cout << "------------------" << endl;
    (!(!(!M))).output();
}
