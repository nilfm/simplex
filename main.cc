#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"
#include "Simplex.hh"

const bool BLAND = false; //indica si es fa servir regla de Bland

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
    Simplex::Resultat res_faseI;
    if (BLAND) res_faseI = Simplex::faseI_bland(A, b, c);
    else res_faseI = Simplex::faseI_cost_negatiu(A, b, c);

    // Obtencio de B i B inversa
    Matrix B(m, m);  //matriu basica
    Simplex::obtenir_matriu_basica(A, B, res_faseI.vB);
    Matrix B_inv = B.inverse(); //B^(-1)
    Row xB = B_inv*b; //valor de les variables basiques
    
    // Obtencio de z
    double z = Simplex::calcular_z(res_faseI.vB, res_faseI.xB, c);
    
    // Fase II del Simplex - dues versions
    // Fem que faseII tingui tots els parametres per copia ja que nomes es crida una vegada
    // I aixi no cal fer copies manualment per cridar dos vegades
    // Retornem els resultats per mitja d'una struct creada al namespace Simplex
    Simplex::Resultat res_faseII;
    if (BLAND) res_faseII = Simplex::faseII_bland(A, b, c, res_faseI.vB, res_faseI.vN, res_faseI.xB, z);
    else res_faseII = Simplex::faseII_cost_negatiu(A, b, c, res_faseI.vB, res_faseI.vN, res_faseI.xB, z);
    
}

