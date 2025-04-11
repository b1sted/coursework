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
        printf("Введите целое число: ");
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
    bool valid = false;

    do {
        printf("Хотите продолжить? (да/нет): ");
        // Считываем строку ввода
        if (scanf("%9s", input) != 1) {
            // Если произошла ошибка ввода, очищаем буфер
            while(getchar() != '\n');
            continue;
        }

        // Преобразуем строку в нижний регистр для корректного сравнения
        to_lower_str(input);

        // Сравниваем введённое значение с допустимыми
        if (strcmp(input, "да") == 0) {
            return true;
        } else if (strcmp(input, "нет") == 0) {
            return false;
        } else {
            printf("Некорректный ввод. Пожалуйста, введите 'да' или 'нет'.\n");
            valid = false;
        }
    } while (!valid);

    return false;
}
