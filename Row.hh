#ifndef _ROW_CLASS_
#define _ROW_CLASS_

#include "Includes.hh"

class Row{
private:
    vector<double> row;
    
public:
    //Constructores
    Row();
    Row(int size, double x);
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
    double norm_1() const;
    double norm_2() const;
    double norm_p(double p) const;
    double norm_inf() const;

    //Operadors
    double& operator[](int x);
    Row operator+(Row r);
    double operator*(Row r);
    Row operator*(double d);
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
Row operator*(double d, Row r);

#endif
