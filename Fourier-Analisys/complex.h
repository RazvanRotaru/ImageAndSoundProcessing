#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

typedef struct COMPLEX {
    double a;
    double b;

    COMPLEX(double a = 0, double b = 0) : a(a), b(b) {}

    COMPLEX& operator=(const COMPLEX& x) {
        a = x.a;
        b = x.b;
        return *this;
    }
    COMPLEX& operator+=(const COMPLEX& x) {
        a += x.a;
        b += x.b;
        return *this;
    }
    COMPLEX operator+(const COMPLEX& x) const{
        return {x.a + a, x.b + b};
    }
    bool operator==(const COMPLEX& x) const{
        return (x.a == a && x.b == b);
    }
    COMPLEX operator*(const COMPLEX& x) const {
        return {x.a * a - x.b * b, x.a * b + a * x.b};    
    }
    COMPLEX operator*(const double& x) const {
        return {a * x, b * x};    
    }

} complex;

double magnitude(complex x) {
    return sqrt(x.a * x.a + x.b * x.b);
}

double phase(complex x) {
    return atan2(x.b, x.a);
}

complex* makeComplexArray(int16_t* &array, int n) {
    complex* complexArray = new complex[n];

    for (int i = 0; i < n; i++)
        complexArray[i].a = array[i];
    
    delete[] array;
    return complexArray;
}

int16_t* makeRealArray(complex* &x, int N) {
    int16_t* real_x = new int16_t[N];

    for (int i = 0; i < N; i++)
        real_x[i] = x[i].a;

    delete[] x;   
    return real_x;
}
