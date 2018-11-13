#ifndef SIMPLEX_HH
#define SIMPLEX_HH

#include "Includes.hh"
#include "Matrix.hh"
#include "Row.hh"

namespace Simplex {
    struct Resultat {
        Row vB;
        Row vN;
        Row xB;
        double z;
        int status;
    };
    
    /* Deixa en B la matriu basica de les columnes de A
    corresponents als indexs de vB */
    void obtenir_matriu_basica(Matrix& A, Matrix& B, Row& vB);
    
    /* Calcula el valor de la funcio objectiu en el punt donat 
    per xB i amb v.n.b igual a zero */
    double calcular_z(Row& vB, Row& xB, Row& c);
    
    /* Fa la fase I del Simplex i retorna una struct amb la solucio (nomes importa vB i vN).
     * La variable status indica:
     *      -Status = 0 -> s'ha trobat SBF inicial
     *      -Status = 1 -> hi ha encara variables artificials a la base
     *      -Status = 2 -> no s'ha trobat SBF (z > 0) 
     *      -Status = 3 -> cicle detectat (si no Bland) */
    Resultat faseI_cost_negatiu(Matrix A, Row b, Row c, Row vB, Row vN) {
    Resultat faseI_bland(Matrix A, Row b, Row c, Row vB, Row vN);
    
    /* Fa la fase II del Simplex amb els parametres donats. 
     * Retorna una struct amb la solucio, la variable status indica:
     *      -Status = 0 -> s'ha trobat solucio
     *      -Status = 1 -> problema il·limitat 
     *      -Status = 2 -> cicle detectat (si no Bland) */
    Resultat faseII_cost_negatiu(Matrix A, Row b, Row c, Row vB, Row vN, Row xB, double z);
    Resultat faseII_bland(Matrix A, Row b, Row c, Row vB, Row vN, Row xB, double z);
}

#endif
