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
    return GCD(a % b, b);
  }
  return GCD(a, b % a);
}

void Rational::Reduce() {
  int gcd = GCD(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    q_ = -q_;
    p_ = -p_;
  }
}

Rational::Rational() : p_(0), q_(1) {
}

Rational::Rational(int p) {  // NOLINT
  this->p_ = p;
  this->q_ = 1;
}

Rational::Rational(int p, int q) {  // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero{};
  }
  p_ = p;
  q_ = q;
  Reduce();
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int p) {
  p_ = p;
  Reduce();
}

void Rational::SetDenominator(int q) {
  if (q == 0) {
    throw RationalDivisionByZero{};
  }

  q_ = q;
  Reduce();
}

Rational& Rational::operator+=(const Rational& other) {
  p_ = (p_ * other.q_) + (other.p_ * q_);
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  p_ = (p_ * other.q_) - (other.p_ * q_);
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  p_ = p_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.p_ == 0) {
    throw RationalDivisionByZero{};
  }
  p_ = p_ * other.q_;
  q_ = q_ * other.p_;
  Reduce();
  return *this;
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

Rational operator+(Rational first) {
  return first;
}

Rational operator-(Rational first) {
  int p = first.GetNumerator();
  first.SetNumerator(-p);
  return first;
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
  if (other.GetNumerator() == 0) {
    throw RationalDivisionByZero{};
  }
  Rational copy = first;
  copy /= other;
  return copy;
}

bool operator<(const Rational& first, const Rational& other) {
  return (first.GetNumerator() * other.GetDenominator()) < (other.GetNumerator() * first.GetDenominator());
}

bool operator>(const Rational& first, const Rational& other) {
  return (first.GetNumerator() * other.GetDenominator()) > (other.GetNumerator() * first.GetDenominator());
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
  int n = 0;
  int d = 0;
  bool have_minus_n = false;
  bool have_minus_d = false;
  bool have_slash = false;

  std::string num_str;
  is >> num_str;

  int num_size = num_str.size();

  for (int i = 0; i < num_size; ++i) {
    char one_symbol = num_str[i];
    if (one_symbol == '/') {
      have_slash = true;
    } else if (one_symbol == '-') {
      if (!have_slash) {
        have_minus_n = true;
      } else {
        have_minus_d = true;
      }
    } else if (('0' <= one_symbol) && (one_symbol <= '9')) {
      if (!have_slash) {
        n *= 10;
        n += num_str[i] - '0';
      } else {
        d *= 10;
        d += num_str[i] - '0';
      }
    }
  }

  n = (have_minus_n ? (-n) : (n));
  d = (have_minus_d ? (-d) : (d));

  if ((d == 0) && (have_slash)) {
    throw RationalDivisionByZero{};
  }

  first.SetNumerator(1);
  first.SetDenominator(1);
  first.SetNumerator(n);
  first.SetDenominator((have_slash ? (d) : (1)));

  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& first) {
  if (first.GetDenominator() == 1) {
    os << first.GetNumerator();
  } else {
    os << first.GetNumerator() << "/" << first.GetDenominator();
  }

  return os;
}
