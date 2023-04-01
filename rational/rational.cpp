#include "rational.h"

int GCD(int a, int b) {
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
    // int gcd = stD::gcd(p, q); 
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

void Rational::SetNumerator(int p) {
    this->p = p;
    reduce();
}

void Rational::SetDenominator(int q) {
    if (q == 0) {
        throw RationalDivisionByZero{};
        return;
    }
    this->q = q;
    reduce();
    if (q < 0) {
        this->q = -q;
        this->p = -p;
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
    //
}

std::ostream& operator<<(std::ostream& os, const Rational& first) {
    if (first.GetDenominator() == 1) {
        os << first.GetNumerator();
    } else {
        os << first.GetNumerator() << "/" << first.GetDenominator();
    }
    return os;
}

int main() {
    Rational x;        // дробь 5/1
    std::cin >> x;         // ввод: 14/-6, дробь: -7/3 (общий множитель 2; знаменатель > 0)
    std::cout << x;        // вывод: 1/3


    // Rational x = 5;
    // // std::cout << x << "\n";
    // x.SetDenominator(15);
    // // std::cout << x << "\n";
    // Rational y;
    // std::cin >> y;
    // std::cout << y << "\n";
    // y += x;
    // std::cout << y << "\n";
    // Rational a(5,4);
    // Rational c = a + 3;
    // std::cout << c << "\n";
    // std::cout << a << "\n";
    // Rational a(2,3);
    // Rational b(3,4);
    // Rational c;
    // Rational d = 5;
    // std::cout << a << " " << b << " " << c << " " << d << "\n";
    // std::cout << c.GetNumerator() << "/" << c.GetDenominator() << "\n";
    // c.SetNumerator(2);
    // std::cout << c.GetNumerator() << "/" << c.GetDenominator() << "\n";
    // std::cout << c << " " << a << "\n";
    // std::cout << c + a << "\n";
    // std::cout << ++b + 2 << "\n";
    return 0;
}