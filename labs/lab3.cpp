#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
int euclide(int,int);
class Fraction{
    int nom,den;
public:
    Fraction(char*);
    Fraction(int n = 0,int m = 1): nom(n),den(m){};
    void reduce();
    operator char*();
    Fraction operator <=(Fraction);
    int getnom(){return nom;};
    int getden(){return den;};
};
Fraction::Fraction(char* s){
    char *p = strchr(s,'/');
    den = 1;
    if(p != NULL){
        *p++ = '\0';
        den = atoi(p);
    }
    nom = atoi(s);
}
Fraction Fraction::operator<=(Fraction a) {
    int nom1 = a.getnom();
    int den1 = a.getden();
    if(nom*den1 < nom1*den){
        return Fraction(nom,den);
    }else{
        return Fraction(nom1,den1);
    }
}
Fraction::operator char*(){
    static char s[32];
    sprintf(s,"%d/%d",nom,den);
    return s;
}
void Fraction::reduce(){
    int gcd;
    gcd = euclide(abs(nom),den);
    nom/=gcd;
    den /=gcd;
}
int euclide(int n, int d){
    int r = 1;
    while(n != 0){
        r = d%n;
        d = n;
        n = r;
    }
    return d;
}
int main(int argc, char*argv[]){
    if(argc < 2){
        return(puts("Incorrect input"));
    }
    Fraction x(argv[1]);
    Fraction y(argv[2]);
    Fraction c;
    x.reduce();y.reduce();
    c = x <= y;
    cout << (char*)c << endl;
    return 0;
}
