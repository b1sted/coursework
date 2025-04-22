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
#include <string.h>
#include <stdlib.h>

#include "file.h"

// Функция для открытия файлов для последующей записи в них информации
void open_output_files(FILE **f1, FILE **f2, FILE **f3) {
    *f1 = fopen("data/array_t.txt", "w");
    *f2 = fopen("data/array_Uvx.txt", "w");
    *f3 = fopen("data/array_Uvix.txt", "w");

    // Проверка успешности открытия файлов
    if (*f1 == NULL || *f2 == NULL || *f3 == NULL) {
        perror("Ошибка при открытии файлов");
        exit(1); // Завершение программы в случае ошибки
    }
}

// Функция для закрытия файлов
void close_output_files(FILE *f1, FILE *f2, FILE *f3) {
    if (f1) fclose(f1);
    if (f2) fclose(f2);
    if (f3) fclose(f3);
}

// Функция для нахождения размера файлов
long get_file_size(FILE *f) {
    if (fseek(f, 0, SEEK_END) != 0) {
        perror("Ошибка при fseek");
        return 1;
    }

    long size_f = ftell(f);
    if (size_f < 0) perror("Ошибка при ftell");
    return size_f;
}
