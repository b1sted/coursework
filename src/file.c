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
