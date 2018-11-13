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

    // Interpretacio dels resultats de fase I
    if (res_faseI.status == 0) cout << "SBF inicial trobada. Iniciant fase II" << endl;
    else if (res_faseI.status == 1) cout << "Variables artificials amb valor 0 a la base. Finalitzant." << endl;
    else if (res_faseI.status == 2) cout << "No s'ha trobat una SBF a la fase I. Finalitzant." << endl;
    else if (res_faseI.status == 3) cout << "S'ha detectat un cicle en la fase I. Finalitzant." << endl;
    if (res_faseI.status != 0) return 0; //no podem continuar

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
    
    // Interpretacio dels resultats de fase II
    if (res_faseII.status == 0) cout << "Solucio optima trobada." << endl;
    else if (res_faseII.status == 1) cout << "Problema il·limitat." << endl;
    else if (res_faseII.status == 2) cout << "S'ha detectat un cicle en la fase II. Finalitzant." << endl;
    if (res_faseII.status != 0) return 0; //no podem continuar
    
    cout << "Resultats:" << endl;
    cout << "Valor de la funcio objectiu: " << res_faseII.z << endl;
    cout << "Vector solucio:" << endl;
    //fer output de x, amb x_B i x_N ordenats com toca
}

