#include <iostream>
#include "polynomial.h"
#include <sstream>
#include <assert.h>


using namespace std;

void checkOut() {
    stringstream ss;
    ss << Polynomial(0, 2, new int[3]{ 1, 2, 3 }) << " ";
    ss << Polynomial(1, 2, new int[2]{ -3, 4 }) << " ";
    ss << Polynomial(-1, 2, new int[4]{ 1, -3, 0, -1 }) << " ";
    ss << Polynomial() << " ";
    ss << Polynomial(0, 2, new int[3]{ 0, 3, -3 }) << " ";
    ss << Polynomial(-2, 2, new int[5]{ 1, 0, 0, 0, 1 }) << " ";
    assert(ss.str() == "3x^2+2x+1 4x^2-3x -x^2-3+x^-1 0 -3x^2+3x x^2+x^-2 ");
    cout << "Copy to string - Ok!" << endl;
}

void PolynomialOperators() {
    stringstream ss;
    const auto a = Polynomial(0, 2, new int[3]{ 1, 2, 3 });
    const auto b = Polynomial(1, 2, new int[2]{ -3, 4 });
    auto c = Polynomial(-1, 2, new int[4]{ 1, -3, 0, -1 });
    const auto d = Polynomial();
    const auto e = Polynomial(0, 2, new int[3]{ 0, 3, -3 });
    const auto f = Polynomial(-2, 2, new int[5]{ 1, 0, 0, 0, 1 });
    assert(a * b == b * a);
    cout << "a * b == b * a - Ok!" << endl;
    assert(d * e == d);
    cout << "d * e == d - Ok!" << endl;
    assert(a * b * c == a * (b * c));
    cout << "a * b * c == a * (b * c) - Ok!" << endl;
    assert(a * b == Polynomial(1, 4, new int[4]{ -3, -2, -1, 12 }));
    cout << "a * b == Polynomial(1, 4, new int[4]{ -3, -2, -1, 12 }) - Ok!" << endl;
    assert(a + b == b + a);
    cout << "a + b == b + a - Ok!" << endl;
    assert(d + e == e);
    cout << "d + e == e - Ok!" << endl;
    assert(a + b + c == a + (b + c));
    cout << "a + b + c == a + (b + c) - Ok!" << endl;
    assert(5 * a == a * 5);
    cout << "5 * a == a * 5 - Ok!" << endl;
    assert(a + b + c == Polynomial(-1, 2, new int[4]{ 1, -2, -1, 6 }));
    cout << "a + b + c == Polynomial(-1, 2, new int[4]{ 1, -2, -1, 6 }) - Ok!" << endl;
    assert(c / 2 == Polynomial(0, 0, new int[1]{ -1 }));
    cout << "c / 2 == Polynomial(0, 0, new int[1]{ -1 }) - Ok!" << endl;
    assert(c.get(4) == -18.75);
    cout << "c.get(4) == -18.75 - Ok!" << endl;
    assert(a[1] == 2);
    cout << "a[1] == 2 - Ok!" << endl;
    assert(a[10] == 0);
    cout << "a[10] == 0 - Ok!" << endl;
    c[5] = 3;
    assert(c.get(4) == 3053.25);
    cout << "c.get(4) == 3053.25 - Ok!" << endl;
    assert((-c) == (-(-(-c))));
    cout << "(-c) == (-(-(-c))) - Ok!" << endl;
    auto h = -c;
    assert(c[5] == 3 && h[5] == -3);
    assert((-c)[5] == -3);
    cout << "(-c)[5] == -3 - Ok!" << endl;
    auto g = b;
    g[3] = 0;
    assert(g == b);
    cout << "g == b - Ok!" << endl;

    auto s = Polynomial();
    cin >> s; //min max x1 x2 x3 ...
    assert(s[1] == 2);
}


int main() {
    checkOut();
    PolynomialOperators();
    return 0;
}