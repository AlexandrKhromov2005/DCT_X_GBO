#include "population.h"

Population::Population() {
    for(size_t i = 0; i < POP_SIZE; ++i){
        for(size_t j = 0; j < VEC_SIZE; ++j){
            this->vectors[i][j] = TH * (2.0 * rand_num() - 1.0);
        }
    }
}