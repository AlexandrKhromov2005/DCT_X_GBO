#ifndef BLOCK_METRICS_H
#define BLOCK_METRICS_H

#include <cmath>
#include "block.h"

namespace Metrics {

    // Рассчитывает MSE (среднеквадратическую ошибку) между двумя блоками double.
    double calculateMSE(const Block<double>& block1, const Block<double>& block2);

    // Рассчитывает PSNR между двумя блоками double.
    double calculatePSNR(const Block<double>& block1, const Block<double>& block2);

}

#endif // BLOCK_METRICS_H