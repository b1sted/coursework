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

#include "output.h"
#include "file.h"

// Функция вывода заставки из файла
void print_banner() {
    FILE *fp = fopen("data/zast.txt", "r");
    
    if (!fp) {
        perror("Не удалось открыть файл заставки");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

// Функция вывода данных в виде таблицы
void forming_table(int n, float *t, float *Uvx, float *Uvix) {
    printf("----------------------------------------\n");
    printf("|  №  |     t    |    Uvx   |   Uvix   |\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %3d | %8.3f | %8.3f | %8.3f |\n", i, t[i], Uvx[i], Uvix[i]);
    }
    printf("----------------------------------------\n");
}

// Функция для записи данных в файл
void output_in_file(FILE *f1, FILE *f2, FILE *f3, int n, float *t, float *Uvx, float *Uvix) {
    for (int i = 0; i < n; i++) {
        fprintf(f1, "\n %6.3f", t[i]);
        fprintf(f2, "\n %6.3f", Uvx[i]);
        fprintf(f3, "\n %6.3f", Uvix[i]);
    }

    long size_f1 = get_file_size(f1);
    long size_f2 = get_file_size(f2);
    long size_f3 = get_file_size(f3);

    if (size_f1 < 0 || size_f2 < 0 || size_f3 < 0) {
        printf("\nПроизошла ошибка при определении размера файлов.\n");
    } else if (size_f1 == 0 && size_f2 == 0 && size_f3 == 0) {
        printf("\nЗапись в файлы прошла успешно, однако файлы пусты — массивы не были заполнены данными.\n");
    } else {
        printf("\nЗапись данных в файлы произведена успешно.\n");
    }
}
