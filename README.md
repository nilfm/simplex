# Pràctica 2 IO (Símplex)

### Estructura del codi

El codi de C++ que hem escrit per implementar l'algorisme del Símplex primal es divideix en quatre blocs:

+ La classe `Row`, que fa de vector: `Row.cc` i `Row.hh`
+ La classe `Matrix`, que fa de matriu: `Matrix.cc` i `Matrix.hh`
+ El `namespace Simplex`, que conté totes les funcions auxiliars i principals relacionades amb l'algorisme del Símplex: `Simplex.cc` i `Simplex.hh`
+ `main.cc`, que és el programa principal que crida tota la resta

El nostre objectiu amb aquesta estructura és tenir un codi modular, en el qual les parts funcionin independentment una de l'altra. En particular, que la classe `Matrix` ens pugui servir per altres projectes que no tinguin res a veure amb el Símplex.

### Instruccions

Per compilar el codi, només cal executar la comanda `make`, que crida el `Makefile` i genera un executable `main.x`.

Les dades que se li passen al `main.x` han d'estar en el format adequat: primer el vector `c`, després la matriu `A`, i per últim el vector `b`. Hem facilitat les nostres matrius en aquest format, a la mateixa carpeta que el codi.

Per activar o desactivar la regla de Bland, només cal canviar el valor del `const bool BLAND` que hi ha a les primeres línies de `main.cc`.

