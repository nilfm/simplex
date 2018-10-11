#ifndef _ROW_CLASS_
#define _ROW_CLASS_

#include "Includes.hh"

class Row{
private:
    vector<double> row;
    
public:
    //Constructores
    Row(int size, double x);
    Row(int size);
    
    //Destructora
    ~Row();
    
    //Input-Output
    void input();
    void output();
    void output_vertical();

    //Funcions propies dels vectors
    double norm_1();
    double norm_2();
    double norm_p(double p);
    double norm_inf();

    //Operadors
    double& operator[](int x);
    Row operator+(Row& r);
    double operator*(Row& r);
    Row operator*(double d);
    Row operator-();
    Row operator-(Row& r);
    Row& operator=(Row& r);
};


#endif
