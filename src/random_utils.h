#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

// Инициализация генератора случайных чисел
void init_random();

// Генерация случайного числа в диапазоне [0.0, 1.0]
double rand_num();

// Генерация нормально распределенного числа
double randn();

// Генерация значения rho на основе параметра alpha
double new_rho(double alpha);

// Генерация четырёх уникальных индексов
void gen_indexes(int indexes[4], int n, int cur_ind, int best_ind);

// Генерация одного случайного индекса без проверки
int gen_random_index(int n);

double rand_neg_one_to_one();

#ifdef __cplusplus
}
#endif

#endif // RANDOM_UTILS_H
