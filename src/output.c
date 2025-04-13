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
    printf("\n № t Uvx Uvix\n");
    for (int i = 0; i < n; i++) {
        printf(" %3d %6.3f %6.3f %6.3f\n", i, t[i], Uvx[i], Uvix[i]);
    }
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
        printf("Произошла ошибка при определении размера файлов.\n");
    } else if (size_f1 == 0 && size_f2 == 0 && size_f3 == 0) {
        printf("Запись в файлы прошла успешно, однако файлы пусты — массивы не были заполнены данными.\n");
    } else {
        printf("Запись данных в файлы произведена успешно.\n");
    }
}
