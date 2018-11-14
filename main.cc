#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"
#include "Simplex.hh"

const bool BLAND = false;    //indica si es fa servir regla de Bland

int main() {
    cout.setf(ios::fixed);
    cout.precision(PRECISION);
    
    // Input de les dimensions
    int m, n;
    cin >> m >> n;
    // Input de c, A, b
    Row c(n);       //c pertany a R^n
    c.input();
    Matrix A(m, n); //A pertany a R^(mn);
    A.input();
    Row b(m);       //b pertany a R^m
    b.input();
    
    int iteracions;
    // Calcul de SBF inicial per Fase I
    Simplex::Resultat res_faseI = Simplex::faseI(A, b, iteracions, BLAND);

    // Interpretacio dels resultats de fase I
    if (res_faseI.status == 1) cout << "Variables artificials amb valor 0 a la base. Finalitzant." << endl;
    else if (res_faseI.status == 2) cout << "No s'ha trobat una SBF a la fase I. Problema infactible. Finalitzant." << endl;
    else if (res_faseI.status == 3) cout << "S'ha detectat un cicle en la fase I. Degeneració, cal aplicar Bland. Finalitzant." << endl;
    if (res_faseI.status != 0) return 0; //no podem continuar
    
    // Obtencio de z
    res_faseI.z = Simplex::calcular_z(res_faseI.vB, res_faseI.xB, c);
    
    // Fase II del Simplex - dues versions
    // Fem que faseII tingui tots els parametres per copia ja que nomes es crida una vegada
    // Retornem els resultats per mitja d'una struct creada al namespace Simplex
    Simplex::Resultat res_faseII = Simplex::faseII(A, c, res_faseI, iteracions, BLAND);
    
    // Interpretacio dels resultats de fase II
    if (res_faseII.status == 1) cout << "Problema il·limitat." << endl;
    else if (res_faseII.status == 2) cout << "S'ha detectat un cicle en la fase II. Finalitzant." << endl;
    if (res_faseII.status != 0) return 0; //no podem continuar
    
    for (int i = 0; i < res_faseII.vB.size(); i++) res_faseII.vB[i]++;
    for (int i = 0; i < res_faseII.vN.size(); i++) res_faseII.vN[i]++;
    
    // Output de resultats
    cout << "Resultats:" << endl;
    cout << "  VB*: ";
    res_faseII.vB.output();
    cout << "  XB*: ";
    res_faseII.xB.output();
    cout << "  VNB*:";
    res_faseII.vN.output();
    cout << "  r*:  ";
    res_faseII.r.output();
    cout << "  z*:  ";
    cout << setw(PADDING) << res_faseII.z << endl;
}
