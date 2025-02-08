#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

// Инициализация генератора случайных чисел
void init_random();

// Генерация случайного числа в диапазоне [0.0, 1.0]
long double rand_num();

// Генерация нормально распределенного числа
long double randn();

// Генерация значения rho на основе параметра alpha
long double new_rho(long double alpha);

// Генерация четырёх уникальных индексов
void gen_indexes(int indexes[4], int n, int cur_ind, int best_ind);

#ifdef __cplusplus
}
#endif

#endif // RANDOM_UTILS_H
