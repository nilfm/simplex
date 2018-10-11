#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"

int main() {
    Matrix M(3, 3, 3.14);
    M.output();
    M.input();
    M.output();
}
