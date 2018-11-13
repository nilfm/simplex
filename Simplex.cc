#include "Includes.hh"
#include "Simplex.hh"
#include "Matrix.hh"
#include "Row.hh"

void Simplex::obtenir_matriu_basica(Matrix& A, Matrix& B, Row& vB) {
    int m = B.size();
    for (int i = 0; i < m; i++) {
        B.modificar_columna(i, A.columna(vB[i]));
    }
}

double Simplex::calcular_z(Row& vB, Row& xB, Row& c) {
    double res = 0;
    int m = vB.size();
    for (int i = 0; i < m; i++) {
        res += xB[i]*c[vB[i]];
    }
    return res;
}

Simplex::Resultat Simplex::faseI(Matrix A, Row b, Row c, Row vB, Row vN) {
    //TO DO
}

Simplex::Resultat Simplex::faseII_cost_negatiu(Matrix A, Row b, Row c, Row vB, Row vN, Row xB, double z) {
    //TO DO
}

Simplex::Resultat Simplex::faseII_bland(Matrix A, Row b, Row c, Row vB, Row vN, Row xB, double z) {
    //TO DO
}
