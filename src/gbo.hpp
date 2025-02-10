#include <array>
#include "config.h"

class Gbo {
public:
    double f_x_best, f_x_worst;
    int best_ind;
    
    std::array<double, VEC_SIZE> best_x;  
    std::array<double, VEC_SIZE> worst_x;

    std::array<std::array<double, VEC_SIZE>, POP_SIZE> population;
    std::array<double, POP_SIZE> f_values;

    Gbo(
        const std::array<double, VEC_SIZE>& input_best_vec,  
        const std::array<double, VEC_SIZE>& input_worst_vec,
        const std::array<std::array<double, VEC_SIZE>, POP_SIZE>& input_population,
        const std::array<double, POP_SIZE>& input_values
    );

    void main_loop();

    std::array<double, VEC_SIZE> gsr_func(
        double ro1, 
        const std::array<double, VEC_SIZE>& best_x,
        const std::array<double, VEC_SIZE>& worst_x,
        const std::array<double, VEC_SIZE>& x,
        const std::array<double, VEC_SIZE>& x_r1,
        const std::array<double, VEC_SIZE>& dm,
        int eps,
        const  std::array<double, VEC_SIZE> x_m,
        int flag
    );
};
