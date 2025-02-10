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
<<<<<<< HEAD
            //std::array<double, VEC_SIZE> gsr = gsr_func(ro1, best_x, worst_x, population[cur_vec]);
=======
            std::array<double, VEC_SIZE> gsr = gsr_func(ro1, best_x, worst_x, population[cur_vec], population[r1], dm,eps, x_m, flag);
        
            for(int i = 0; i < VEC_SIZE; i++){
                dm[i] = rand_num() * ro * (best_x[i] - population[r1][i]);
            }
    
            std::array<double, VEC_SIZE> x1 = {};
            for(int i = 0; i < VEC_SIZE; i++){
                x1[i] = population[cur_vec][i] - gsr[i] + dm[i]; 
            }
>>>>>>> b499f0d226f9414ac4df4353b1e155359c46b94d




            dm = {};
            for(int i = 0; i < VEC_SIZE; i++){
                dm[i] = rand_num() * ro * (population[r1][i] - population[r2][i]);
            }
            
            flag = 2;
            gsr = gsr_func(ro1, best_x, worst_x, population[cur_vec], population[r1], dm,eps, x_m, flag);
        
            for(int i = 0; i < VEC_SIZE; i++){
                dm[i] = rand_num() * ro * (population[r1][i] - population[r2][i]);
            }
    
            std::array<double, VEC_SIZE> x2 = {};
            for(int i = 0; i < VEC_SIZE; i++){
                x2[i] = best_x[i] - gsr[i] + dm[i]; 
            }

            std::array<double, VEC_SIZE> x_new = {};
            for(int i = 0; i < VEC_SIZE; i++){
                ro = alpha * (2.0 * rand_num() - 1.0);
                double x3 = population[cur_vec][i] - ro * (x2[i] - x1[i]);
                double ra = rand_num();
                double rb = rand_num();
                x_new[i] = ra * (rb * x1[i] + (1 - rb) * x2[i]) + (1 - ra) * x3;
            }

            if(rand_num() < PR){

                std::array<double, VEC_SIZE> y = {};
                if(rand_num() < 0.5){
                    y = x_new;
                }
                else{
                    y = best_x;
                }

                double mu1 = rand_num();
                double mu2 = rand_num();

                double u1, u2, u3;
                if(mu1 < 0.5){
                    u1 = 2.0 * rand_num();
                    u2 = rand_num();
                    u3 = rand_num(); 
                }
                else{
                    u1 = 1;
                    u2 = 1;
                    u3 = 1;
                }

                if(mu2 < 0.5){
                    x_m = gen_vec();
                }
                else{
                    x_m = population[gen_random_index(POP_SIZE)];
                }

                double f1 = rand_neg_one_to_one();
                double f2 = rand_neg_one_to_one();

                for(int i = 0; i < VEC_SIZE; i++){
                    x_new[i] = y[i] + f1 * (u1 * best_x[i] - u2 * x_m[i]) + f2 * ro1 * (u3 * (x2[i] - x1[i]) + u2 * (population[r1][i] - population[r2][i])) / 2.0;
                }
            }
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
    const  std::array<double, VEC_SIZE>& x_m,
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

std::array<double, VEC_SIZE> Gbo::gen_vec(){
    std::array<double, VEC_SIZE> x = {};
    for(int i = 0; i < VEC_SIZE; i++){ 
        x[i] = TH * (2.0 * rand_num() - 1.0);
    }

    return x;
}

void Gbo::new_vec_check(std::array<double, VEC_SIZE>& x_new, int cur_vec){
    for(int i = 0; i < VEC_SIZE; i++){
        if(x_new[i] < -TH){
            x_new[i] = -TH;
        }
        else if(x_new[i] > TH){
            x_new[i] = TH;
        }
    }

    double f_x_new = 0;

    if(f_x_new < f_values[cur_vec]){
        population[cur_vec] = x_new;
        f_values[cur_vec] = f_x_new;
        if(f_values[cur_vec] < f_x_best){
            best_x = population[cur_vec];
            f_x_best = f_values[cur_vec];
        }
    }

    if(f_values[cur_vec] > f_x_worst){
        worst_x = population[cur_vec];
        f_x_worst = f_values[cur_vec];
    }
}