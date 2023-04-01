#ifndef RATIONAL
#define RATIONAL
#include <iostream>
#include <numeric>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};


class Rational {
private:
    int p;
    int q;
    
    void reduce();
public:
    Rational(int, int);
    int GetNumerator() const;    
    int GetDenominator() const;
    void SetNumerator(int);
    void SetDenominator(int);
    Rational& operator+=(const Rational&);
    Rational& operator-=(const Rational&);
    Rational& operator*=(const Rational&);
    Rational& operator/=(const Rational&);
    Rational operator+();
    Rational operator-();
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
};
Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);
bool operator<(const Rational&, const Rational&);
bool operator>(const Rational&, const Rational&);
bool operator==(const Rational&, const Rational&);
bool operator!=(const Rational&, const Rational&);
bool operator<=(const Rational&, const Rational&);
bool operator>=(const Rational&, const Rational&);
std::istream& operator>>(std::istream&, Rational&);
std::ostream& operator<<(std::ostream&, const Rational&);


#endif