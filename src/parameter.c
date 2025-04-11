#include <stdio.h>
#include <math.h>

#include "parameter.h"
#include "forming.h"

#define N 1500

// Функция расчета длительности переднего фронта импульса
float calc_leading_edge(int n, float *U, float dt) {
    // Находим максимальное и минимальное значения
    float Umax = U[0], Umin = U[0];
    for (int i = 0; i < n; i++) {
        if (U[i] > Umax) Umax = U[i];
        if (U[i] < Umin) Umin = U[i];
    }

    // Рассчитываем пороговые уровни
    float U1 = Umin + 0.9 * (Umax - Umin);
    float U2 = Umin + 0.1 * (Umax - Umin);

    // Считаем длительность заднего фронта
    float duration = 0;
    for (int i = 0; i < n - 1; i++) {
        if (U[i] < U1 && U[i] > U2 && U[i + 1] > U[i]) duration += dt;
    }

    return duration;
}

// Функция расчета параметра с заданной точностью
void calculate_with_precision() {
    float epsilon = 0.01; // Требуемая точность (1%)
    float current_precision = 1.0; // Текущая погрешность
    float prev_parameter = 1e10; // Начальное (очень большое) значение 
    int n = 11; // Начальное количество точек

    float current_parameter, t[N], Uvx[N], Uvix[N], dt;

    while (current_precision > epsilon) {
        // Формирование массивов
        forming_time(n, t, &dt);
        
        float t1 = 10, t2 = 15, t3 = 45, a = 20, b = 0.5, c = 17;
        forming_Uvx(n, t, Uvx, t1, t2, t3, a, b, c);
        float Uvx1 = 20, d = 2, e = -5;
        forming_Uvix(n, Uvx, Uvix, Uvx1, d, e);

        // Расчет параметра
        current_parameter = calc_leading_edge(n, Uvix, dt);

        // Расчет погрешности
        if (prev_parameter != 1e10) {
            current_precision = fabs(prev_parameter - current_parameter) / current_parameter;
        }

        printf("n = %d, параметр = %f, погрешность = %f\n", n, current_parameter, current_precision);

        // Обновление значений для следующей итерации
        prev_parameter = current_parameter;
        n *= 2;
    }

    if (n >= N) {
        printf("Предупреждение: достигнут максимальный размер массива без достижения требуемой точности\n");
    } else {
        printf("Итоговое значение параметра: %f (точность: %f)\n", current_parameter, current_precision);
    }
}
