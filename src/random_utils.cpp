#include <random>
#include <ctime>
#include <cmath>
#include <climits>
#include <cstring>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

static std::mt19937 generator;
static std::uniform_real_distribution<long double> distribution(0.0L, 1.0L);
static bool initialized = false;

// Инициализация генератора случайных чисел
void init_random() {
    if (!initialized) {
        generator.seed(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }
}

// Генерация случайного числа в диапазоне [0.0, 1.0]
long double rand_num() {
    init_random();
    return distribution(generator);
}

// Генерация нормально распределенного числа (метод Бокса-Мюллера)
long double randn() {
    static bool has_next = false;
    static long double next_value;

    if (has_next) {
        has_next = false;
        return next_value;
    }

    long double u1 = rand_num();
    long double u2 = rand_num();

    long double r = std::sqrt(-2.0L * std::log(u1));
    long double theta = 2.0L * 3.14159265358979323846264338327950288419716939937510L * u2;

    long double z0 = r * std::cos(theta);
    next_value = r * std::sin(theta);

    has_next = true;
    return z0;
}

// Генерация значения rho на основе параметра alpha
long double new_rho(long double alpha) {
    return (2.0L * rand_num() * alpha) - alpha;
}

// Генерация четырёх уникальных индексов
void gen_indexes(int indexes[4], int n, int cur_ind, int best_ind) {
    int cnt = 0;
    bool used_indices[VEC_SIZE];
    memset(used_indices, 0, sizeof(bool) * n);
    used_indices[cur_ind] = true;
    used_indices[best_ind] = true;

    while (cnt < 4) {
        int temp = generator() % n;
        if (!used_indices[temp]) {
            indexes[cnt++] = temp;
            used_indices[temp] = true;
        }
    }
}

#ifdef __cplusplus
}
#endif
