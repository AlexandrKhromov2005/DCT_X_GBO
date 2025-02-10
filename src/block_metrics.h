#ifndef BLOCK_METRICS_H
#define BLOCK_METRICS_H

#include <cmath>
#include "block.h" 

template <typename T>
class Block;

double calculateMSE(const Block<double>& block1, const Block<double>& block2);
double calculatePSNR(const Block<double>& block1, const Block<double>& block2);


#endif // BLOCK_METRICS_H