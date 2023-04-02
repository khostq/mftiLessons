#include "rational.h"

int GCD(int a, int b) {
  a = (a > 0 ? a : -a);
  b = (b > 0 ? b : -b);
  if (a % b == 0) {
    return b;
  }
  if (b % a == 0) {
    return a;
  }
  if (a > b) {
    return GCD(a%b, b);
  }
  return GCD(a, b%a);
}

void Rational::reduce() {
  int gcd = GCD(p, q);
  p /= gcd;
  q /= gcd;
}

Rational::Rational(int p = 0, int q = 1) { // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero{};
  } else {
    this->p = p;
    this->q = q;
    reduce();
    if (q < 0) {
      this->q = -q;
      this->p = -p;
    }
  }
  
}

int Rational::GetNumerator() const {
  return p;
}

int Rational::GetDenominator() const {
  return q;
}

void Rational::SetNumerator(int p, bool reduce_this = true) {
  this->p = p;
  if (reduce_this) {
    reduce();
  }
}

void Rational::SetDenominator(int q, bool reduce_this = true) {
  if (q == 0) {
    throw RationalDivisionByZero{};
    return;
  }
  this->q = q;
  if (q < 0) {
    this->q = -q;
    this->p = -p;
  }
  if (reduce_this) {
    reduce();
  }
}

Rational& Rational::operator+=(const Rational& other) {
  p = (p * other.q) + (other.p * q);
  q = q * other.q;
  reduce();
  return *this; 
}

Rational& Rational::operator-=(const Rational& other) {
  p = (p * other.q) - (other.p * q);
  q = q * other.q;
  reduce();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  p = p * other.p;
  q = q * other.q;
  reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (p == 0) {
    throw RationalDivisionByZero{};
  } else {
    p = p * other.q;
    q = q * other.p;
    reduce();
    return *this;
  }
} 

Rational Rational::operator+() {
  return *this;
}

Rational Rational::operator-() {
  Rational copy = *this;
  copy.p = -copy.p;
  return copy;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) { 
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator--() { 
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}


Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}

Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}

Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}

Rational operator/(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy /= other;
  return copy;
}

bool operator<(const Rational& first, const Rational& other) {
  return ((first.GetNumerator() * other.GetDenominator()) < (other.GetNumerator() * first.GetDenominator()) ? true : false);
}

bool operator>(const Rational& first, const Rational& other) {
  return ((first.GetNumerator() * other.GetDenominator()) > (other.GetNumerator() * first.GetDenominator()) ? true : false);
}

bool operator==(const Rational& first, const Rational& other) {
  return !((first < other) || (first > other));
}

bool operator!=(const Rational& first, const Rational& other) {
  return !(first == other);
}

bool operator<=(const Rational& first, const Rational& other) {
  return ((first < other) || (first == other));
}

bool operator>=(const Rational& first, const Rational& other) {
  return ((first > other) || (first == other));
}

std::istream& operator>>(std::istream& is, Rational& first) {
  int chisl = 0;
  int znam = 0;
  bool minus_chisl = false;
  bool minus_znam = false;
  bool slash = false;
  std::string str;
  std::cin >> str;
  int size = str.size();
  for (int i = 0; i < size; ++i) {
    char one_symbol = str[i];
    if (one_symbol == '/') {
      slash = true;
    } else if (one_symbol == '-') {
      (!slash ? (minus_chisl = true) : (minus_znam = true));
    } else if (('0' <= one_symbol) && (one_symbol <= '9')) {
      (slash ? ({znam *= 10; znam += str[i] - '0';}) : ({chisl *= 10; chisl += str[i] - '0';}));
    }
  }
  (minus_chisl ? chisl = -chisl : chisl = chisl);
  (minus_znam ? znam = -znam : znam = znam);

  first.SetNumerator(chisl, false);
  first.SetDenominator((slash ? znam : 1), false);
  first.reduce();
  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& first) {
  if (first.GetDenominator() == 1) {
    os << first.GetNumerator();
  } else {
    os << first.GetNumerator() << "/" << first.GetDenominator();
  }
  os << "\n";
  return os;
}

int main() {
  Rational x = 5;        // дробь 5/1
  std::cout << x;        // вывод: 5
  x.SetDenominator(15);  // дробь 1/3 (5/15 сократилась)
  std::cout << x;        // вывод: 1/3
  std::cin >> x;
  std::cout << x;
}