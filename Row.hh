#ifndef _ROW_CLASS_
#define _ROW_CLASS_

#include "Includes.hh"

class Row{
private:
    vector<long double> row;
    
public:
    //Constructores
    Row();
    Row(int size, long double x);
    Row(int size);
    
    //Destructora
    ~Row();
    
    //Funcions basiques
    int size() const;
    Row permute(Row& perm);
    
    //Input-Output
    void input();
    void output() const;
    void output_vertical() const;

    //Funcions propies dels vectors
    long double norm_1() const;
    long double norm_2() const;
    long double norm_p(long double p) const;
    long double norm_inf() const;

    //Operadors
    long double& operator[](int x);
    Row operator+(Row r);
    long double operator*(Row r);
    Row operator*(long double d);
    Row operator-();
    Row operator-(Row r);
    Row& operator=(Row r);
    Row& operator+=(Row r);
    Row& operator-=(Row r);
    bool operator>=(Row b);
    bool operator>(Row b);
    bool operator<=(Row b);
    bool operator<(Row b);
};

//Altres operadors
Row operator*(long double d, Row r);

#endif
