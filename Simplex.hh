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
        Row r;
        Matrix B_inv;
        long double z;
        int status;
    };
    
    /* Retorna la matriu basica de les columnes de A
    corresponents als indexs de vB */
    Matrix obtenir_matriu_basica(Matrix& A, Row& vB);
    /* Retorna la matriu no basica de les columnes de A
    corresponents als indexs de vN */
    Matrix obtenir_matriu_no_basica(Matrix& A, Row& vN);
    /* Retorna els costos basics de c en una matriu 1xm */
    Row obtenir_costos_basics(Row& c, Row& vB);
    /* Retorna els costos no basics de c en una matriu 1x(n-m) */
    Row obtenir_costos_no_basics(Row& c, Row& vN);


    /* Calcula el valor de la funcio objectiu en el punt donat 
    per xB i amb v.n.b igual a zero */
    long double calcular_z(Row& vB, Row& xB, Row& c);
    
    /* Donat A, retorna A|I, si A es mxn, A|I es mx(n+m) */
    Matrix ampliar(Matrix& A);
    
    /* Donat A, retorna la matriu resultant d'eliminar les files redundants de A */
    Matrix reduir(Matrix& A);
    
    /* Donada la inversa anterior, la direccio basica de la variable sortint, i l'index p,
    retorna la nova inversa */
    Matrix actualitzacio_inversa(Matrix& B_inv, Row& dB, int p);
    
    /* Escriu en el format adequat l'output de cada iteracio */
    void write_status(int iter, int q, long double rq, int p, long double theta, long double z);
    
    /* Fa una iteracio de fase I o fase II del Simplex i retorna un int amb el status actual
    res queda modificat d'acord amb la iteracio.
    *       -Retorna 0: continua
    *       -Retorna 1: optim trobat
    *       -Retorna 2: il·limitat   */ 
    int iteracio(Matrix& A, Row& c, Resultat& res, bool bland, int iter);


    /* Fa la fase I del Simplex i retorna una struct amb la solucio (nomes importa vB i vN).
     * La variable status indica:
     *      -Status = 0 -> s'ha trobat SBF inicial
     *      -Status = 1 -> hi ha encara variables artificials a la base
     *      -Status = 2 -> no s'ha trobat SBF (z > 0) 
     *      -Status = 3 -> cicle detectat (si no Bland) */
    Resultat faseI(Matrix A, Row b, int& iteracions, bool bland);

    
    /* Fa la fase II del Simplex amb els parametres donats. 
     * Retorna una struct amb la solucio, la variable status indica:
     *      -Status = 0 -> s'ha trobat solucio
     *      -Status = 1 -> problema il·limitat 
     *      -Status = 2 -> cicle detectat (si no Bland) */
    Resultat faseII(Matrix A, Row c, Resultat res, int iteracions, bool bland);
}

#endif
