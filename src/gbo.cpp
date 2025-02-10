#include "gbo.hpp"
#include "config.h"
#include <cmath>
#include "random_utils.h"

Gbo::Gbo(
    const std::array<double, VEC_SIZE>& input_best_vec,  
    const std::array<double, VEC_SIZE>& input_worst_vec,
    const std::array<std::array<double, VEC_SIZE>, POP_SIZE>& input_population,
    const std::array<double, POP_SIZE>& input_values
) :
best_x(input_best_vec),  
worst_x(input_worst_vec),
population(input_population),
f_values(input_values)
{}

void Gbo::main_loop(){
    for(int cur_iter = 0; cur_iter < ITERRATIONS; cur_iter++){
        double beta = 0.2 + (1.2 - 0.2) * pow((1 - pow((static_cast<double>(cur_iter) + 1.0) / ITERRATIONS, 3.0)), 2.0);
        double alpha = abs(beta * sin((3.0 * PI / 2.0 + sin(3.0 * PI / 2.0 * beta))));

        for(int cur_vec = 0; cur_vec < POP_SIZE; cur_vec++){
            int rand_indexes[4];
            gen_indexes(rand_indexes, POP_SIZE, cur_vec, best_ind);

            int r1 = rand_indexes[0];
            int r2 = rand_indexes[1];
            int r3 = rand_indexes[2];
            int r4 = rand_indexes[3];

            std::array<double, VEC_SIZE> x_m = {};
            for(int i = 0; i < VEC_SIZE; i++){
                x_m[i] = (population[r1][i] + population[r2][i] + population[r3][i] + population[r4][i]) / 4.0;
            }

            double ro = new_rho(alpha);
            double ro1 = new_rho(alpha);

            double eps = 0.05;

            std::array<double, VEC_SIZE> dm = {};
            for(int i = 0; i < VEC_SIZE; i++){
                dm[i] = rand_num() * ro * (best_x[i] - population[r1][i]);
            }

            int flag = 1;
            //std::array<double, VEC_SIZE> gsr = gsr_func(ro1, best_x, worst_x, population[cur_vec]);


        }
    }
}

std::array<double, VEC_SIZE> Gbo::gsr_func(
    double ro1, 
    const std::array<double, VEC_SIZE>& best_x,
    const std::array<double, VEC_SIZE>& worst_x,
    const std::array<double, VEC_SIZE>& x,
    const std::array<double, VEC_SIZE>& x_r1,
    const std::array<double, VEC_SIZE>& dm,
    int eps,
    const  std::array<double, VEC_SIZE> x_m,
    int flag
){
    std::array<double, VEC_SIZE> delta = {};
    for(int i = 0; i < VEC_SIZE; i++){
        delta[i] = 2 * rand_num() * abs(x_m[i] - x[i]);
    }

    std::array<double, VEC_SIZE> step = {};
    for(int i = 0; i < VEC_SIZE; i++){
        step[i] = ((best_x[i] - x_r1[i]) + delta[i]) / 2.0;
    }

    std::array<double, VEC_SIZE> del_x = {};
    for(int i = 0; i < VEC_SIZE; i++){
        del_x[i] = population[gen_random_index(POP_SIZE)][i] * abs(step[i]);
    }

    std::array<double, VEC_SIZE> gsr = {};
    for(int i = 0; i < VEC_SIZE; i++){
        gsr[i] = randn() * ro1 * (2.0 * del_x[i] * x[i]) / (best_x[i] - worst_x[i] + eps);
    }

    std::array<double, VEC_SIZE> x_s = {};  
    if(flag == 1){
        for(int i = 0; i < VEC_SIZE; i++){
            x_s[i] = x[i] - gsr[i] + dm[i];
        }
    }
    else{
        for(int i = 0; i < VEC_SIZE; i++){
            x_s[i] = best_x[i] - gsr[i] + dm[i];
        }
    }  

    std::array<double, VEC_SIZE> p = {};
    for(int i = 0; i < VEC_SIZE; i++){
        p[i] = rand_num() * (0.5 * (x_s[i] + x[i]) + rand_num() * del_x[i]);
    }

    std::array<double, VEC_SIZE> q = {};
    for(int i = 0; i < VEC_SIZE; i++){
        q[i] = rand_num() * (0.5 * (x_s[i] + x[i]) - rand_num() * del_x[i]);
    }


    for(int i = 0; i < VEC_SIZE; i++){
        gsr[i] = randn() * ro1 * (2 * del_x[i] * x[i]) / (p[i] - q[i] + eps);
    }

    return gsr;
}