#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"
#include "Simplex.hh"

const bool BLAND = false; //indica si es fa servir regla de Bland
const int n = 20;
const int m = 10;

int main() {
    cout.setf(ios::fixed);
    cout.precision(PRECISIO);
    
    // Input de c, A, b
    Row c(n);       //c pertany a R^n
    c.input();
    Matrix A(m, n); //A pertany a R^(mn);
    A.input();
    Row b(m);       //b pertany a R^m
    b.input();
    
    // Calcul de SBF inicial per Fase I
    Simplex::Resultat res_faseI = Simplex::faseI(A, b, BLAND);

    // Interpretacio dels resultats de fase I
    if (res_faseI.status == 0) cout << "SBF inicial trobada. Iniciant fase II" << endl;
    else if (res_faseI.status == 1) cout << "Variables artificials amb valor 0 a la base. Finalitzant." << endl;
    else if (res_faseI.status == 2) cout << "No s'ha trobat una SBF a la fase I. Finalitzant." << endl;
    else if (res_faseI.status == 3) cout << "S'ha detectat un cicle en la fase I. Finalitzant." << endl;
    if (res_faseI.status != 0) return 0; //no podem continuar

    // Obtencio de B i B inversa
    Matrix B = Simplex::obtenir_matriu_basica(A, res_faseI.vB);
    Matrix B_inv = B.inverse(); //B^(-1)
    Row xB = B_inv*b; //valor de les variables basiques
    
    // Obtencio de z
    res_faseI.z = Simplex::calcular_z(res_faseI.vB, res_faseI.xB, c);
    
    // Fase II del Simplex - dues versions
    // Fem que faseII tingui tots els parametres per copia ja que nomes es crida una vegada
    // I aixi no cal fer copies manualment per cridar dos vegades
    // Retornem els resultats per mitja d'una struct creada al namespace Simplex
    Simplex::Resultat res_faseII = Simplex::faseII(A, b, c, res_faseI, BLAND);
    
    // Interpretacio dels resultats de fase II
    if (res_faseII.status == 0) cout << "Solucio optima trobada." << endl;
    else if (res_faseII.status == 1) cout << "Problema il·limitat." << endl;
    else if (res_faseII.status == 2) cout << "S'ha detectat un cicle en la fase II. Finalitzant." << endl;
    if (res_faseII.status != 0) return 0; //no podem continuar
    
    cout << "Resultats:" << endl;
    cout << "VB*" << endl;
    res_faseII.vB.output();
    cout << "XB*" << endl;
    res_faseII.xB.output();
    cout << "VNB*" << endl;
    res_faseII.vN.output();
    cout << "r*" << endl;
    res_faseII.r.output();
    cout << "z*" << endl;
    cout << res_faseII.z << endl;
}

