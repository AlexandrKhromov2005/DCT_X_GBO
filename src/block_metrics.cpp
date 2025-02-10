#include "block_metrics.h"
#include <limits>
#include "block.h" 


    double calculateMSE(const Block<double>& block1, const Block<double>& block2) {
        double mse = 0.0;
        for (std::size_t i = 0; i < 8; i++) {
            for (std::size_t j = 0; j < 8; j++) {
                double diff = block1.mat[i][j] - block2.mat[i][j];
                mse += diff * diff;
            }
        }
        return mse / 64.0; 
    }

    double calculatePSNR(const Block<double>& block1, const Block<double>& block2) {
        double mse = calculateMSE(block1, block2);
        if (mse == 0) {
            return std::numeric_limits<double>::infinity(); 
        }
        return 10.0 * std::log10((255.0 * 255.0) / mse);
    }
