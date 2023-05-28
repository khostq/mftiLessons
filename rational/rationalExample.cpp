#include <iostream>


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

class Rational {
private:
    int p;
    int q;

    void reduce() {
        int gcd = GCD(p, q); 
        p /= gcd;
        q /= gcd;
    }

public:
    Rational(int p = 0, int q = 1) {
        this->p = p;
        this->q = q;
        reduce();
        if (q < 0) {
            this->q = -q;
            this->p = -p;
        }
    }

    int GetNumerator() const {
        return p;
    }
    
    int GetDenominator() const {
        return q;
    }

    void SetNumerator(int p) {
        this->p = p;
        reduce();
    }

    void SetDenominator(int q) {
        this->q = q;
        reduce();
        if (q < 0) {
            this->q = -q;
            this->p = -p;
        }
    }

    Rational& operator+=(const Rational& other) {
        p = (p * other.q) + (other.p * q);
        q = q * other.q;
        reduce();
        return *this; 
    }

    Rational& operator-=(const Rational& other) {
        p = (p * other.q) - (other.p * q);
        q = q * other.q;
        reduce();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        p = p * other.p;
        q = q * other.q;
        reduce();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        p = p * other.q;
        q = q * other.p;
        reduce();
        return *this;
    } 

    Rational operator+() {
        return *this;
    }

    Rational operator-() {
        Rational copy = *this;
        copy.p = -copy.p;
        return copy;
    }

    Rational& operator++() {
        *this += 1;
        return *this;
    }

    Rational operator++(int) { 
        Rational copy = *this;
        ++*this;
        return copy;
    }

    Rational& operator--() { 
        *this -= 1;
        return *this;
    }

    Rational operator--(int) {
        Rational copy = *this;
        --*this;
        return copy;
    }
};

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
    // return ((first.GetNumerator() * other.GetDenominator()) == (other.GetNumerator() * first.GetDenominator()) ? true : false);
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

std::istream& operator>>(std::istream& is, const Rational& first) {
    is >> first.GetNumerator() >> first.GetDenominator();
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

int main() {
    Rational a(2,3);
    Rational b(3,4);
    Rational c;
    Rational d = 5;
    std::cout << a << " " << b << " " << c << " " << d << "\n";
    std::cout << c.GetNumerator() << "/" << c.GetDenominator() << "\n";
    c.SetNumerator(2);
    std::cout << c.GetNumerator() << "/" << c.GetDenominator() << "\n";
    std::cout << c << " " << a << "\n";
    std::cout << c + a << "\n";
    std::cout << ++b + 2 << "\n";
    return 0;
}