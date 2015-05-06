#include "rational.h"
#include <iostream>

using namespace std;

int gcd(int a,int b){
    if (a < b)
        return gcd(b,a);
    while (b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Rational Rational::simplify(){
    int comm = gcd(this->num, this->den);
    if (num == 0 && den == 0){
        cout << "this is not right" << *this << endl;
        return *this;
    }
    return Rational(this->num / comm, this->den / comm);
}

Rational::Rational(int num, int den): num(num), den(den){}
Rational::Rational(): num(0), den(1){}
Rational::Rational(int num): num(num), den(1){}

Rational Rational::operator-() const{
    return Rational(-this->num, den).simplify();
}

Rational Rational::operator+(const Rational& o)const{
    int comm = gcd(this->den, o.den);
    int newDen = this->den * o.den / comm;
    int mult = this->den / comm;
    int otherMult = o.den / comm;
    int newNum = mult * o.num + otherMult * this->num;
    return Rational(newNum, newDen).simplify();
}

Rational Rational::operator+(const int& o) const{
    return (*this) + Rational(o);
}

Rational Rational::operator-(const Rational& o) const{
    return (*this) + (-o);
}

Rational Rational::operator-(const int& o) const{
    return (*this) + Rational(-o);
}

Rational Rational::operator=(const Rational& o) {
    this->num = o.num;
    this->den = o.den;
    return *this;
}

bool Rational::operator<(const Rational& o) const{
    return o.den * this->num < o.num * this->den;
}

bool Rational::operator>(const Rational& o) const{
    return o < *this;
}

bool Rational::operator<=(const Rational& o) const{
    return ! (*this > o);
}

bool Rational::operator>=(const Rational& o) const{
    return ! (*this < o);
}

bool Rational::operator==(const Rational& o) const{
    int comm_o = gcd(o.num, o.den);
    int comm_this = gcd(this->num, this->den);
    return (o.num / comm_o == this->num / comm_this) &&
            (o.den / comm_o == this->den / comm_this);
}

Rational Rational::operator*(const Rational& o) const{
    return Rational(this->num * o.num, this->den * o.den).simplify();
}

Rational Rational::operator/(const Rational& o) const{
    return Rational(this->num * o.den, this->den * o.num).simplify();
}

Rational Rational::operator*(const int& c) const{
    return Rational(this->num * c, this->den).simplify();
}

Rational Rational::operator+=(const Rational& o) {
    Rational ans = *this + o;
    this->num = ans.num;
    this->den = ans.den;
    return *this;
}

Rational Rational::operator-=(const Rational& o) {
    Rational ans = *this - o;
    this->num = ans.num;
    this->den = ans.den;
    return *this;
}

Rational operator*(const int& c, const Rational& r) {
    return r * c;
}

int Rational::toInt() const{
    return num / den;
}

double Rational::toDouble() const{
    return (double) num / (double) den;
}

ostream& operator<<(ostream& out, Rational& rat){
    if (rat.den != 1)
        out << rat.num << "/" << rat.den;
    else
        out << rat.num;
    return out;
}
