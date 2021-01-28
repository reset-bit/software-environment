#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

double f(double x) {
    return 1 / (1 + x * x);
}

double  intergrate(double(*fp)(double), double a, double b, int precision) {
    fp = f;
    precision = (b - a) * precision;
    double dx = (double)1 / precision;
    double s = 0;
    for (int i = 1; i <= precision; i++) {
        s += f(a + dx) * dx;
        a += dx;
    }
    return s;
}

int main() {
    int precision = 1000;
    cout << "pi = " << 4 * intergrate(f, 0, 1, precision) << endl;
    return 0;
}
