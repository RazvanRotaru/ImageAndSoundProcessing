#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "complex.h"

using namespace std;

complex euler(double x) {
    return {cos(x), sin(x)};
}

complex* fourier(complex* &x, int N) {
    complex* X = new complex[N];

    for (int k = 0; k < N; k++)
        for (int n = 0; n < N; n++)
            X[k] += x[n] * euler(-2 * M_PI * k * n / N);

    delete[] x;
    return X;
}

complex* inverse_fourier(complex* &X, int N) {
    complex* x = new complex[N];

    for (int n = 0; n < N; n++)
        for (int k = 0; k < N; k++)
            x[n] += X[k] * euler(2 * M_PI * k * n / N) * (1.0 / N);

    delete[] X;
    return x;
}

int* extractSpikes(complex* &x, int N) {
    int* spikes = new int[N/2];
    int index = 0;
    
    for (int i = 0; i < N / 2; i++)
        spikes[i] = 0;

    for (int i = 0; i < N / 2; i++) {
        double currMagnitude = magnitude(x[i]);
        if (currMagnitude > magnitude(x[i+1])) {
            for (int j = 0; j <= index; j++) {
                if (currMagnitude > magnitude(x[spikes[j]])) {
                    for (int k = ++index; k > j; k--)
                        spikes[k] = spikes[k-1];
                    spikes[j] = i;
                    break;
                }
            }
        }
    }

    int* ans = new int[index];
    for (int i = 0; i < index; i++)
        ans[i] = spikes[i];
    
    delete[] spikes;
    return ans;
}
