#include "Includes.hh"
#include "Simplex.hh"
#include "Matrix.hh"
#include "Row.hh"

Matrix Simplex::obtenir_matriu_basica(Matrix& A, Row& vB) {
    int m = A.size();
    Matrix B(m, m);
    for (int i = 0; i < m; i++) {
        B.modificar_columna(i, A.columna(vB[i]));
    }
    return B;
}

Matrix Simplex::obtenir_matriu_no_basica(Matrix& A, Row& vN) {
    int m = A.size();
    int n = A[0].size();
    Matrix An(m, n-m);
    for (int i = 0; i < n-m; i++) {
        An.modificar_columna(i, A.columna(vN[i]));
    }
    return An;
}

Row Simplex::obtenir_costos_basics(Row& c, Row& vB) {
    int m = vB.size();
    Row cB(m);
    for (int i = 0; i < m; i++) {
        cB[i] = c[vB[i]];
    }
    return cB;
}

Row Simplex::obtenir_costos_no_basics(Row& c, Row& vN) {
    int k = vN.size();
    Row cN(k);
    for (int i = 0; i < k; i++) {
        cN[i] = c[vN[i]];
    }
    return cN;
}

long double Simplex::calcular_z(Row& vB, Row& xB, Row& c) {
    long double res = 0;
    int m = vB.size();
    for (int i = 0; i < m; i++) {
        res += xB[i]*c[vB[i]];
    }
    return res;
}

Matrix Simplex::ampliar(Matrix& A) {
    int m = A.size();
    int n = A[0].size();
    Matrix M(m, n+m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n+m; j++) {
            if (j < n) M[i][j] = A[i][j];
            else if (j == n+i) M[i][j] = 1;
        }
    }
    return M;
}

Matrix Simplex::actualitzacio_inversa(Matrix& B_inv, Row& dB, int p) {
    int n = B_inv.size();
    Matrix E(n, n, 0);
    for (int i = 0; i < n; ++i) E[i][i] = 1;
    for (int i = 0; i < n; i++) {
        if (i == p) E[i][p] = -1/dB[p];
        else E[i][p] = -dB[i]/dB[p];
    }
    return E*B_inv;
}

void Simplex::write_status(int iter, int q, long double rq, int p, long double theta, long double z) {
    printf("  Iteracio %2d : q = %2d, rq = %*.*f, B(p) = %2d, theta* = %*.*f, z = %*.*f\n", 
    iter, q+1, PADDING, PRECISION, (double)rq, p+1, PADDING, PRECISION, (double)theta, PADDING, PRECISION, (double)z);
}

int Simplex::iteracio(Matrix& A, Row& c, Resultat& res, bool bland, int iter) {
    //Obtenim les mides de A
    int m = A.size();
    int n = A[0].size();
    //Obtenim c_N i c_B
    Row cN = Simplex::obtenir_costos_no_basics(c, res.vN);
    Row cB = Simplex::obtenir_costos_basics(c, res.vB);
    //Obtenim B i A_N
    Matrix B = Simplex::obtenir_matriu_basica(A, res.vB);
    Matrix A_N = Simplex::obtenir_matriu_no_basica(A, res.vN);
    
    //Costos reduits
    res.r = cN - cB*res.B_inv*A_N;
    
    //Si r >= 0, s'ha trobat l'optim
    if (res.r >= Row(n-m, 0)) {
        write_status(iter, -1, 0, -1, 0, res.z);
        return 1;
    }
    
    //Busquem la variable que entra, per Bland o be per cost reduit mes negatiu
    int q = 0;
    if (bland) {
        int lowest = n;
        for (int i = 0; i < n-m; ++i) {
            if (res.r[i] < 0 and res.vN[i] < lowest) {
                q = i;
                lowest = res.vN[i];
            }
        }
    }
    else {
        int lowest = res.r[0];
        for (int i = 1; i < n-m; ++i) {
            if (res.r[i] < lowest) {
                lowest = res.r[i];
                q = i;
            }
        }
    }
    
    //res.vN[q] es la variable que entrara a la base
    
    //Direccio basica factible relacionada a la variable vN[q]
    Row dB = -res.B_inv*A.columna(res.vN[q]);
    
    //Si la DBF (de descens) es positiva, ens trobem en cas il·limitat
    if (dB >= Row(m, 0)) {
        write_status(iter, -1, 0, -1, 0, res.z);
        return 2; //problema il.limitat
    }
    
    //Busquem la p, index de la variable basica que surt de la base
    long double theta = 1e100; //infinit
    int p = 0;
    for (int i = 0; i < m; ++i) {
        if (dB[i] < 0) {
            long double cand = -res.xB[i]/dB[i];
            if (cand < theta or (cand == theta and res.vB[p] > res.vB[i])) {
                p = i;
                theta = cand;
            }
        }
    }
    
    //Actualitzacio de la inversa
    res.B_inv = Simplex::actualitzacio_inversa(res.B_inv, dB, p);
    
    //Actualitzacio de totes les variables
    res.xB = res.xB + theta*dB;
    res.xB[p] = theta;
    res.z = res.z + theta*res.r[q];
    write_status(iter, res.vN[q], res.r[q], res.vB[p], theta, res.z);
    swap(res.vB[p], res.vN[q]);
    
    return 0; //podem continuar
}

Simplex::Resultat Simplex::faseI(Matrix A, Row b, int& iteracions, bool bland) {
    cout << "Fase I" << endl;
    //Obtenim les mides de A
    int m = A.size();
    int n = A[0].size();
    
    //Creem el vector de costos de la fase I
    Row c(n+m, 0);
    for (int i = n; i < n+m; i++) c[i] = 1;
    
    //Creem la nova matriu A_I de la fase I, concatenant amb la identitat
    Matrix A_I = Simplex::ampliar(A);
    
    Simplex::Resultat res;
    //Creem el vector de variables basiques
    res.vB = Row(m);
    for (int i = 0; i < m; i++) res.vB[i] = n+i;
    //Creem el vector de variables no basiques
    res.vN = Row(n);
    for (int i = 0; i < n; i++) res.vN[i] = i;
    //Obtenim la matriu B = B^(-1) = identitat
    res.B_inv = Matrix::identitat(m);
    //Obtenim xB = B_inv*b = id*b = b
    res.xB = b;
    //Calculem z a partir del que tenim
    res.z = calcular_z(res.vB, res.xB, c);
    //Inicialitzem els costos reduits amb la seva mida
    res.r = Row(n-m);
    
    int iter = 1;
    int current = 0;
    while (current == 0) {
        //Anem iterant la fase I pel Simplex primal
        current = iteracio(A_I, c, res, bland, iter);
        iter++;
    }
    
    //Interpretem els resultats obtinguts per retornar status
    if (res.z > TOLERANCIA) res.status = 2;
    else {
		bool ok = true;
		
		for (int i = 0; i < m; i++) {
			if (res.vB[i] >= n) ok = false;
		}
		if (!ok) res.status = 1;
		else res.status = 0;
	}
    //falta el cas status = 3
    
    //Retornem les iteracions, les necessitarem per l'output de la fase II
    iteracions = iter;
    return res;
}

Simplex::Resultat Simplex::faseII(Matrix A, Row c, Resultat res, int iteracions, bool bland) {
    cout << "Fase II" << endl;
    //Obtenim les mides de A
    int m = A.size();
    int n = A[0].size();
    
    //Treiem les variables artificials de vN
    Row vN_copia = res.vN;
    res.vN = Row(n-m);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (vN_copia[i] < n) res.vN[k++] = vN_copia[i];
    }
    
    //Recalculem z amb el vector c que ens donen a les dades
    res.z = calcular_z(res.vB, res.xB, c);
    
    //Inicialitzem els costos reduits amb la seva mida
    res.r = Row(n-m);
    int iter = iteracions;
    int current = 0;
    while (current == 0) {
        //Anem iterant la fase II pel Simplex primal
        current = iteracio(A, c, res, bland, iter);
        iter++;
    }
    //Interpretem els resultats per retornar el status
    //Mirar simplex.hh per saber la codificacio emprada
    res.status = current-1;
    return res;
}
