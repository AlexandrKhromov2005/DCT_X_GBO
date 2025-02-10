#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <utility>
#include "config.h"
#include "block_metrics.h"

// Тип для координат: первая компонента — номер строки, вторая — номер столбца.
using coords = std::pair<std::size_t, std::size_t>;

constexpr std::array<std::pair<std::size_t, std::size_t>, 11> REG0 = {
    std::make_pair(5, 1), std::make_pair(6, 1), std::make_pair(7, 1),
    std::make_pair(3, 3), std::make_pair(4, 3), std::make_pair(5, 3),
    std::make_pair(1, 5), std::make_pair(2, 5), std::make_pair(3, 5),
    std::make_pair(0, 7), std::make_pair(1, 7)
};

constexpr std::array<std::pair<std::size_t, std::size_t>, 11> REG1 = {
    std::make_pair(6, 0), std::make_pair(7, 0),
    std::make_pair(4, 2), std::make_pair(5, 2), std::make_pair(6, 2),
    std::make_pair(2, 4), std::make_pair(3, 4), std::make_pair(4, 4),
    std::make_pair(0, 6), std::make_pair(1, 6), std::make_pair(2, 6)
};

constexpr std::array<std::pair<std::size_t, std::size_t>, 22> ZONE0 = {
    std::make_pair(6,0), std::make_pair(5,1), std::make_pair(4,2),std::make_pair(3,3),
    std::make_pair(2,4), std::make_pair(1,5), std::make_pair(0,6),std::make_pair(0,7),
    std::make_pair(1,6), std::make_pair(2,5), std::make_pair(3,4),std::make_pair(4,3),
    std::make_pair(5,2), std::make_pair(6,1), std::make_pair(7,0),std::make_pair(7,1),
    std::make_pair(6,2), std::make_pair(5,3), std::make_pair(4,4),std::make_pair(3,5),
    std::make_pair(2,6), std::make_pair(1,7)
};

// Шаблон типа для матриц 8x8
template <typename T>
using Matrix = std::array<std::array<T, 8>, 8>;

// Класс, представляющий блок изображения с оригинальными пикселями и DCT-обработанным блоком.
template <typename T>
class Block {
public:
    Matrix<T> mat;

    inline double getRegSum(const std::array<coords, VEC_SIZE / 2>& region) {
        double sum = 0.0;
        for (const auto& crd : region) {
            sum += mat[crd.first][crd.second];
        }
        return sum;
    }

    inline Block apply_x (std::array<double, VEC_SIZE> x, const std::array<coords, VEC_SIZE>& zone) {
        Block<double> new_block = *this;
        int cnt = 0;
        for (const auto& crd : region) {
            new_block.mat[crd.first][crd.second] = SIGN(new_block.mat[crd.first][crd.second]) * fabs(fabs(new_block.mat[crd.first][crd.second]) + x[cnt]);
        }
        return new_block;
    }

    inline double objective_function(unsigned char bit){
        Block new_block = apply_x(x, REG0);
        double s0 = new_block.getRegSum(REG0) == 0? 0.0001 : new_block.getRegSum(REG0);
        double s1 = new_block.getRegSum(REG1) == 0? 0.0001 : new_block.getRegSum(REG1);
        
        if (bit == 0){
            return(s1 / s0) - calculatePSNR(*this, new_block);
        } else {
            return (s0 / s1)- calculatePSNR(*this, new_block);
        }
    }
};

namespace DCT {

    // Определяем тип для матриц с различными элементами
    using Matrix8Double = Matrix<double>;
    using Matrix8UChar = Matrix<unsigned char>;

    // Умножение двух 8x8 матриц: result = a * b.
    void multiplyMatrices(const Matrix8Double& a, const Matrix8Double& b, Matrix8Double& result);

    // Преобразование блока пикселей (unsigned char) в блок коэффициентов (double)
    void convertToDouble(const Matrix8UChar& src, Matrix8Double& dest);

    // Преобразование блока коэффициентов (double) в блок пикселей (unsigned char) с округлением и ограничением [0,255].
    void convertToUChar(const Matrix8Double& src, Matrix8UChar& dest);

    // Константные матрицы базиса для DCT.
    extern const Matrix8Double c;
    extern const Matrix8Double c_t;

    // Функция прямого DCT: на вход подается блок пикселей, на выходе — блок DCT-коэффициентов.
    void dct_func(const Matrix8UChar& block, Matrix8Double& dct_block);

    // Функция обратного DCT: на вход подается блок DCT-коэффициентов, на выходе — блок пикселей.
    void rev_dct_func(Matrix8UChar& block, const Matrix8Double& dct_block);
}

#endif // BLOCK_H
