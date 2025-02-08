#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <array>
#include "config.h"
#include <utility>
#include "random_utils.h"

using popVec = std::array<double, VEC_SIZE>;

class Population {
public:
    std::array<popVec, POP_SIZE> vectors;
    
    Population::Population();
    
};
#endif //POPULATION_H
