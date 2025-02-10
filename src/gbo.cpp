#include "gbo.hpp"
#include "config.h"
#include <cmath>
#include "random_utils.h"

static const double PI = 3.14159265358979323846264338327950288419716939937510;

Gbo::Gbo(
    const std::array<double, VEC_SIZE>& input_best_vec,  
    const std::array<double, VEC_SIZE>& input_worst_vec,
    const std::array<std::array<double, VEC_SIZE>, POP_SIZE>& input_population,
    const std::array<double, POP_SIZE>& input_values
) :
best_vec(input_best_vec),  
worst_vec(input_worst_vec),
population(input_population),
f_values(input_values)
{}

void Gbo::main_loop(){
    for(int cur_iter = 0; cur_iter < ITERRATIONS; cur_iter++){
        double beta = 0.2 + (1.2 - 0.2) * std::pow((1 - std::pow((static_cast<double>(cur_iter) + 1.0) / ITERRATIONS, 3.0)), 2.0);
        double alpha = std::abs(beta * std::sin((3.0 * PI / 2.0 + std::sin(3.0 * PI / 2.0 * beta))));

        for(int cur_vec = 0; cur_vec < POP_SIZE; cur_vec++){
            int rand_indexes[4];
            gen_indexes(rand_indexes, POP_SIZE, cur_vec, best_ind);

            std::array<double, VEC_SIZE> r1 = population[rand_indexes[0]];
            std::array<double, VEC_SIZE> r2 = population[rand_indexes[0]];
            std::array<double, VEC_SIZE> r3 = population[rand_indexes[0]];
            std::array<double, VEC_SIZE> r4 = population[rand_indexes[0]];

            std::array<double, VEC_SIZE> x_m;
            for(int i = 0; i < VEC_SIZE; i++){
                x_m[i] = (r1[i] + r2[i] + r3[i] + r4[i]) / 4.0;
            }

            //ro = new_rho()
            double eps = 0.05;

        }
    }
}
