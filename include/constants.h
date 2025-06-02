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

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Для input.c
#define INPUT_SIZE 10

// Для parameter.c и signal_analysis.c
#define ARRAY_SIZE 1500

// Для parameter.c
#define EPSILON 0.01f
#define INITIAL_CURRENT_PRECISION 1.0f
#define PREV_PARAMETER_INITIAL 1e10f
#define INITIAL_POINTS 11

// Параметры для функции forming_Uvx (используются в forming.c)
#define T1_PARAM 10.0f
#define T2_PARAM 15.0f
#define T3_PARAM 45.0f
#define A_PARAM 20.0f
#define B_PARAM 0.5f
#define C_PARAM 17.0f

// Параметры для функции forming_Uvix (используются в forming.c)
#define UVX1_PARAM 20.0f
#define D_PARAM 2.0f
#define E_PARAM -5.0f

// Параметры для функции forming_time (используются в forming.c)
#define TN_PARAM 5.0f
#define TK_PARAM 50.0f

// Пути к файлам
#define FILE_PATH_ARRAY_T "data/array_t.txt"
#define FILE_PATH_ARRAY_UVX "data/array_Uvx.txt"
#define FILE_PATH_ARRAY_UVIX "data/array_Uvix.txt"
#define FILE_PATH_ZAST "data/zast.txt"

#endif // CONSTANTS_H
