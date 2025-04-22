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
#include <stdbool.h>
#include <math.h>

#include "input.h"
#include "output.h"
#include "file.h"
#include "forming.h"
#include "parameter.h"

#define N 1500

int main() {
    float t[N], Uvx[N], Uvix[N], dt;
    int n, choice;
    bool continueProgram = true;

    print_banner();

    while (continueProgram) {
        printf("\nМеню:\n");
        printf("1. Контрольный расчет для n точек\n");
        printf("2. Расчет параметра с заданной точностью\n");
        printf("3. Запись данных в файл\n");
        printf("Выберите опцию: ");

        int scanf_result = scanf(" %d", &choice); // Сохраняем результат scanf

        if (scanf_result != 1) { // Проверяем, прочитала ли scanf ровно одно целое число
            printf("Ошибка ввода. Пожалуйста, введите целое число.\n");
            // Очистка буфера ввода
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // Просто читаем и выбрасываем символы до конца строки или файла
            }
            choice = -1; // Присваиваем 'choice' недопустимое значение, чтобы избежать случайного выхода (если было 0)
                        // или повторного выполнения предыдущего case. -1 попадет в default.
        }

        switch (choice) {
        case 1:
            n = input_n();

            forming_time(n, t, &dt);

            float t1 = 10, t2 = 15, t3 = 45, a = 20, b = 0.5, c = 17;
            forming_Uvx(n, t, Uvx, t1, t2, t3, a, b, c);

            float Uvx1 = 20, d = 2, e = -5;
            forming_Uvix(n, Uvx, Uvix, Uvx1, d, e);

            forming_table(n, t, Uvx, Uvix);

            break;
        case 2:
            calculate_with_precision();
            break;
        case 3:
            FILE *f1, *f2, *f3;

            // Открываем файлы для записи
            open_output_files(&f1, &f2, &f3);

            // Записываем данные в файлы
            output_in_file(f1, f2, f3, n, t, Uvx, Uvix);
            
            // Закрываем файлы после записи
            close_output_files(f1, f2, f3);
            break;
        }

        printf("\n");
        continueProgram = ask_user_continue();
    }
    
    return 0;
}
