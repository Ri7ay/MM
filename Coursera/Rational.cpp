#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include<set>
#include <exception>
using namespace std;

long gcf_nums(long num_f, long num_s) {
    while (num_f > 0 && num_s > 0) {
        if (num_f > num_s) {
            num_f %= num_s;
        } else {
            num_s %= num_f;
        }
    }
    return num_f + num_s;
}

class Rational {
public:
    Rational() {
        num = 0;
        denom = 1;
    }

    Rational(long numerator, long denominator) {
        long gcf;
        if (denominator == 0) {
            throw  invalid_argument("Invalid argument");
        }
        if (numerator * denominator == 0) {
            num = 0;
            denom = 1;
        } else if (numerator * denominator > 0) {
            numerator = fabs(numerator);
            denominator = fabs(denominator);
            gcf = gcf_nums(numerator, denominator);
            num = numerator / gcf;
            denom = denominator / gcf;
        } else {
            numerator = fabs(numerator);
            denominator = fabs(denominator);
            gcf = gcf_nums(numerator, denominator);
            num = -numerator / gcf;
            denom = denominator / gcf;
        }
    }

    long Numerator() const {
        return num;
    }

    long Denominator() const {
        return denom;
    }

private:
    long num, denom;
};

Rational operator+(const Rational& num_f, const Rational& num_s) {
    return {num_f.Numerator() * num_s.Denominator() + num_s.Numerator() * num_f.Denominator(),
            num_f.Denominator() * num_s.Denominator()};
}

Rational operator-(const Rational& num_f, const Rational& num_s) {
    return {num_f.Numerator() * num_s.Denominator() - num_s.Numerator() * num_f.Denominator(),
            num_f.Denominator() * num_s.Denominator()};
}

Rational operator*(const Rational& num_f, const Rational& num_s) {
    return {num_f.Numerator() * num_s.Numerator(), num_f.Denominator() * num_s.Denominator()};
}

Rational operator/(const Rational& num_f, const Rational& num_s) {
    if (num_s.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    return  {num_f.Numerator() * num_s.Denominator(), num_f.Denominator() * num_s.Numerator()};
}

bool operator==(const Rational& num_f, const Rational& num_s) {
    return (num_f.Numerator() == num_s.Numerator() && num_f.Denominator() == num_s.Denominator());
}

bool operator<(const Rational& num_f, const Rational& num_s) {
    Rational fract = num_f - num_s;
    return fract.Numerator() < 0;
}

istream& operator>>(istream& stream, Rational& fract) {
    long num = fract.Numerator(), denom = fract.Denominator();
    if (stream) {
        stream >> num;
        stream.ignore(1);
        stream >> denom;
        Rational fract_tmp(num, denom);
        fract = fract_tmp;
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& num) {
    stream << num.Numerator() << "/" << num.Denominator();
    return stream;
}

int main() {
    Rational fract_f, fract_s;
    char oper;
    try {
        cin >> fract_f >> oper >> fract_s;
    }
    catch (invalid_argument& ex) {
        cout << ex.what() << endl;
        return EXIT_FAILURE;
    }
    if (oper == '+') {
        cout << fract_f + fract_s;
    } else if (oper == '-') {
        cout << fract_f - fract_s;
    } else if (oper == '*') {
        cout << fract_f * fract_s;
    } else if (oper == '/') {
        try {
            fract_f / fract_s;
            cout << fract_f / fract_s;
        }
        catch (domain_error& ex) {
            cout << ex.what() << endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}