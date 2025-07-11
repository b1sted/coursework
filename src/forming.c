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

#include "forming.h"

// Параметры для функции forming_time
static const float TN_PARAM = 5.0f;
static const float TK_PARAM = 50.0f;

// Параметры для функции forming_Uvx
static const float T1_PARAM = 10.0f;
static const float T2_PARAM = 15.0f;
static const float T3_PARAM = 45.0f;
static const float A_PARAM  = 20.0f;
static const float B_PARAM  = 0.5f;
static const float C_PARAM  = 17.0f;

// Параметры для функции forming_Uvix
static const float UVX1_PARAM = 20.0f;
static const float D_PARAM    = 2.0f;
static const float E_PARAM    = -5.0f;

// Функция формирования массива времени
void forming_time(int n, float *t, float *dt) {
    *dt = (TK_PARAM - TN_PARAM) / (n - 1);
    for (int i = 0; i < n; i++) {
        t[i] = TN_PARAM + i * (*dt);
    }
}

// Функция формирования массива Uvx
void forming_Uvx(int n, float *t, float *Uvx) {
    for (int i = 0; i < n; i++) {
        if (t[i] <= T1_PARAM) {
            Uvx[i] = 0;
        } else if (T1_PARAM < t[i] && t[i] <= T2_PARAM) {
            Uvx[i] = A_PARAM * (t[i] - T1_PARAM);
        } else if (T2_PARAM < t[i] && t[i] <= T3_PARAM) {
            Uvx[i] = A_PARAM * (T2_PARAM - T1_PARAM) - B_PARAM * (t[i] - T2_PARAM);
        } else {
            Uvx[i] = A_PARAM * (T2_PARAM - T1_PARAM) - B_PARAM * (T3_PARAM - T1_PARAM) - C_PARAM * (t[i] - T3_PARAM);
        }
    }
}

// Функция формирования массива Uvix
void forming_Uvix(int n, float *Uvx, float *Uvix) {
    for (int i = 0; i < n; i++) {
        if (Uvx[i] <= UVX1_PARAM) {
            Uvix[i] = D_PARAM * Uvx[i] + E_PARAM;
        } else {
            Uvix[i] = D_PARAM * UVX1_PARAM + E_PARAM;
        }
    }
}
