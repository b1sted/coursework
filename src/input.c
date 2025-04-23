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
#include <ctype.h>
#include <stdbool.h>

#include "input.h"

#define INPUT_SIZE 10

// Функция для ввода n
int input_n() {
    int value;
    int result;
    
    while (1) {
        printf("\nВведите целое число: ");
        result = scanf("%d", &value);
        if (result == 1) {
            break;  // Ввод успешно прочитан
        } else {
            printf("Ошибка ввода. Попробуйте еще раз.\n");
            // Очистка буфера ввода до символа новой строки
            while(getchar() != '\n');
        }
    }
    return value;
}

// Функция для преобразования строки к нижнему регистру
void to_lower_str(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Функция для запроса пользователя на продолжение работы
bool ask_user_continue(void) {
    char input[INPUT_SIZE];

    while (1) {
        printf("Хотите продолжить? (да/нет): ");

        // Считываем строку ввода с ограничением
        if (scanf("%9s", input) != 1) {
            while (getchar() != '\n'); // Если произошла ошибка ввода, очищаем буфер
            continue;
        }

        // Очищаем буфер ввода до символа новой строки
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Преобразуем строку в нижний регистр для корректного сравнения
        to_lower_str(input);

        // Сравниваем введённое значение с допустимым
        if (strcmp(input, "да") == 0) {
            return true;
        } else if (strcmp(input, "нет") == 0) {
            return false;
        } else {
            printf("Некорректный ввод. Пожалуйста, введите 'да' или 'нет'.\n");
        }
    }

    return false; // Эта строка никогда не выполнится, но предотвращает предупреждение
                  // компилятора о отсутствии возвращаемого значения функции, которая
                  // должна возвращать значение
}
