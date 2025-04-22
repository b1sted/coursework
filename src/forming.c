/*
 * SPDX-FileCopyrightText: Copyright (c) 2025 Nikita Mandrykin. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

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
