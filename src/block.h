#ifndef DCT_H
#define DCT_H

#include <utility>
#include <array>
#include "config.h"

using coords = std::pair<size_t, size_t>; // первое значени - строчка, второе - столбец
using pixelBlock = std::array<std::array<unsigned char, 8>, 8>;
using freqBlock = std::array<std::array<double, 8>, 8>;

class Block {
public:
    pixelBlock original;
    freqBlock dct_processed;
    inline double getRegSum(std::array<coords, POP_SIZE> region);
};

#endif //DCT_H
