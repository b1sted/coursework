#include <stdio.h>
#include "output.h"

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
void output_in_file(int n, float *t, float *Uvx, float *Uvix) {
    FILE *f1, *f2, *f3;

    f1 = fopen("data/array_t.txt", "w");
    f2 = fopen("data/array_Uvx.txt", "w");
    f3 = fopen("data/array_Uvix.txt", "w");

    for (int i = 0; i < n; i++) {
        fprintf(f1, "\n %6.3f", t[i]);
        fprintf(f2, "\n %6.3f", Uvx[i]);
        fprintf(f3, "\n %6.3f", Uvix[i]);
    }

    printf("Запись данных в файлы произведена успешно\n");

    fclose(f1);
    fclose(f2);
    fclose(f3);
}
