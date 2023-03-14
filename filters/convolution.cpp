#include "convolution.h"

void Convolution::Process(Image& input) {
    auto matrix = input.GetMatrix();
    auto result = matrix;
    const size_t height = input.GetHeight();
    const size_t width = input.GetWidth();

    for (int y = 0; y < static_cast<int>(height); ++y) {
        for (int x = 0; x < static_cast<int>(width); ++x) {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int ty = std::clamp<int>(y + dy, 0, height - 1);
                    int tx = std::clamp<int>(x + dx, 0, width - 1);
                    sum_red += convolution_matrix_[dy + 1][dx + 1] * matrix[ty][tx].red;
                    sum_green += convolution_matrix_[dy + 1][dx + 1] * matrix[ty][tx].green;
                    sum_blue += convolution_matrix_[dy + 1][dx + 1] * matrix[ty][tx].blue;
                }
            }
            result[y][x].red = std::clamp(sum_red, 0, 255);
            result[y][x].green = std::clamp(sum_green, 0, 255);
            result[y][x].blue = std::clamp(sum_blue, 0, 255);
        }
    }
    input = Image(result);
}

Convolution::Convolution(Matrix convolution_matrix) : convolution_matrix_(convolution_matrix) {
}
