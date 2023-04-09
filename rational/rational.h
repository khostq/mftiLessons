#ifndef RATIONAL
#define RATIONAL
#include <iostream>
#include <numeric>
#include <string>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int p);         // NOLINT
  Rational(int p, int q);  // NOLINT
  Rational(const Rational& r);

  int GetNumerator() const;
  int GetDenominator() const;

  void SetNumerator(int);
  void SetDenominator(int);

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  Rational& operator++();
  Rational& operator--();

  Rational operator++(int);
  Rational operator--(int);

 private:
  int p_;
  int q_;
  void Reduce();
};

Rational operator+(Rational first);
Rational operator-(Rational first);

Rational operator+(const Rational& first, const Rational& other);
Rational operator-(const Rational& first, const Rational& other);
Rational operator*(const Rational& first, const Rational& other);
Rational operator/(const Rational& first, const Rational& other);

bool operator<(const Rational& first, const Rational& other);
bool operator>(const Rational& first, const Rational& other);
bool operator==(const Rational& first, const Rational& other);
bool operator!=(const Rational& first, const Rational& other);
bool operator<=(const Rational& first, const Rational& other);
bool operator>=(const Rational& first, const Rational& other);

std::istream& operator>>(std::istream& is, Rational& first);
std::ostream& operator<<(std::ostream& os, const Rational& first);

#endif