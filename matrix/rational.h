#ifndef __RAT__H__

#define __RAT__H__

#include <ostream>

class Rational{
    int num;
    int den;

    public:

        Rational(int, int);
        Rational(int);
        Rational();
        Rational simplify();

        Rational operator-() const;
        Rational operator+(const Rational&) const;
        Rational operator-(const Rational&) const;
        Rational operator/(const Rational&) const;
        Rational operator*(const Rational&) const;
        Rational operator*(const int&) const;
        Rational operator+=(const Rational&);
        Rational operator-=(const Rational&);

        int toInt() const;
        double toDouble() const;
        friend std::ostream& operator<<(std::ostream&, Rational&);
};

Rational operator*(const int&, const Rational&) ;


#endif
