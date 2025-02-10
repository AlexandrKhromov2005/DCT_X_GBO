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
static std::uniform_real_distribution<double> distribution(0.0, 1.0);
static bool initialized = false;

// Инициализация генератора случайных чисел
void init_random() {
    if (!initialized) {
        generator.seed(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }
}

// Генерация случайного числа в диапазоне [0.0, 1.0]
double rand_num() {
    init_random();
    return distribution(generator);
}

// Генерация нормально распределенного числа (метод Бокса-Мюллера)
double randn() {
    static bool has_next = false;
    static double next_value;

    if (has_next) {
        has_next = false;
        return next_value;
    }

    double u1 = rand_num();
    double u2 = rand_num();

    double r = std::sqrt(-2.0 * std::log(u1));
    double theta = 2.0 * PI * u2;

    double z0 = r * std::cos(theta);
    next_value = r * std::sin(theta);

    has_next = true;
    return z0;
}

// Генерация значения rho на основе параметра alpha
double new_rho(double alpha) {
    return (2.0 * rand_num() * alpha) - alpha;
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

// Генерация одного случайного индекса без проверки
int gen_random_index(int n) {
    return generator() % n;  // Генерация случайного индекса
}

// Генерация случайного числа в диапазоне от -1 до 1 включительно
double rand_neg_one_to_one() {
    return 2.0 * rand_num() - 1.0;  // Генерация числа от -1 до 1
}

#ifdef __cplusplus
}
#endif
