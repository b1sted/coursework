#include <stdio.h>

#include "forming.h"

// Функция формирования массива времени
void forming_time(int n, float *t, float *dt) {
    float tn = 5, tk = 50;

    *dt = (tk - tn) / (n - 1);
    for (int i = 0; i < n; i++) {
        t[i] = tn + i * (*dt);
    }
}

// Функция формирования массива Uvx
void forming_Uvx(int n, float *t, float *Uvx, float t1, float t2, float t3, float a, float b, float c) {
    for (int i = 0; i < n; i++) {
        if (t[i] <= t1) {
            Uvx[i] = 0;
        } else if (t1 < t[i] && t[i] <= t2) {
            Uvx[i] = a * (t[i] - t1);
        } else if (t2 < t[i] && t[i] <= t3) {
            Uvx[i] = a * (t2 - t1) - b * (t[i] - t2);
        } else {
            Uvx[i] = a * (t2 - t1) - b * (t3 - t1) - c * (t[i] - t3);
        }
    }
}

// Функция формирования массива Uvix
void forming_Uvix(int n, float *Uvx, float *Uvix, float Uvx1, float a, float b) {
    for (int i = 0; i < n; i++) {
        if (Uvx[i] <= Uvx1) {
            Uvix[i] = a * Uvx[i] + b;
        } else {
            Uvix[i] = a * Uvx1 + b;
        }
    }
}
