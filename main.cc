#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"
#include "Simplex.hh"

int main() {
    // Input de les dimensions del problema
    int n, m;
    cin >> n >> m;
    
    // Input de c, A, b
    Row c(n);       //c pertany a R^n
    c.input();
    Matrix A(m, n); //A pertany a R^(mn);
    A.input();
    Row b(m);       //b pertany a R^m
    b.input();
    
    // Calcul de SBF inicial per Fase I
    Row vB(m);       //llista de variables basiques
    Row vN(n-m);     //llista de variables no basiques
    Simplex::Resultat res_faseI = Simplex::faseI(A, b, c, vB, vN);

    // Obtencio de B i B inversa
    Matrix B(m, m);  //matriu basica
    Simplex::obtenir_matriu_basica(A, B, vB);
    Matrix B_inv = B.inverse(); //B^(-1)
    Row xB = B_inv*b; //valor de les variables basiques
    
    // Obtencio de z
    double z = Simplex::calcular_z(vB, xB, c);
    
    // Fase II del Simplex - dues versions
    // Fem que faseII tingui tots els parametres per copia ja que nomes es crida una vegada
    // I aixi no cal fer copies manualment per cridar dos vegades
    // Retornem els resultats per mitja d'una struct creada al namespace Simplex
    Simplex::Resultat resultat1 = Simplex::faseII_cost_negatiu(A, b, c, vB, vN, xB, z);
    Simplex::Resultat resultat2 = Simplex::faseII_bland(A, b, c, vB, vN, xB, z);
    
}

