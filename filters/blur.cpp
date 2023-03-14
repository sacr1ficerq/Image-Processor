#include "blur.h"

#include <chrono>
#include <cmath>
#include <iostream>

namespace {
double CalculateGaussian(size_t delta_x, size_t delta_y, double sigma) {
    double coefficient = sigma * sigma * 2 * std::numbers::pi_v<double>;
    double degree = (delta_x * delta_x + delta_y * delta_y) / (2 * sigma * sigma);
    double result = exp(-1 * degree) / coefficient;
    return result;
}

size_t Delta(const size_t x1, const size_t x2) {
    return x1 > x2 ? x1 - x2 : x2 - x1;
}

NormalChannel CalculateGaussianMatrix(size_t radius, double sigma) {
    auto start = std::chrono::high_resolution_clock::now();
    NormalChannel matrix(2 * radius, std::vector<double>(2 * radius, 0));
    for (size_t x = 0; x < 2 * radius; ++x) {
        for (size_t y = 0; y < 2 * radius; ++y) {
            matrix[y][x] = CalculateGaussian(x, y, sigma);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto execution_time = duration_cast<std::chrono::seconds>(stop - start).count();

    std::cout << "Matrix built in " << execution_time << " seconds" << std::endl;
    return matrix;
}

NormalRGBMatrix ApplyGaussian(NormalRGBMatrix& matrix, size_t height, size_t width, double sigma) {
    auto new_matrix = matrix;
    const size_t radius = 2 + std::min<size_t>({static_cast<size_t>(std::ceil(3 * sigma)), matrix.red_chanel.size(), matrix.red_chanel[0].size()});
    const auto gauss_matrix = CalculateGaussianMatrix(radius, sigma);

    double accumulation_red;
    double accumulation_green;
    double accumulation_blue;

    for (int x0 = 0; x0 < static_cast<int>(width); ++x0) {
        for (int y0 = 0; y0 < static_cast<int>(height); ++y0) {
            accumulation_red = 0;
            accumulation_green = 0;
            accumulation_blue = 0;

            size_t left_border = x0 < static_cast<int>(radius) ? 0 : (x0 - radius);
            size_t top_border = y0 < static_cast<int>(radius) ? 0 : (y0 - radius);

            if (x0 + radius >= width) {
                left_border = std::max<double>(width - 2 * radius, 0);
            }

            if (y0 + radius >= height) {
                top_border = std::max<double>(height - 2 * radius, 0);
            }

            size_t right_border = std::min<double>(left_border + 2 * radius, width);
            size_t bottom_border = std::min<double>(top_border + 2 * radius, height);

            for (int x = left_border; x < static_cast<int>(right_border); ++x) {
                for (int y = top_border; y < static_cast<int>(bottom_border); ++y) {
                    size_t delta_x = Delta(x0, x);
                    size_t delta_y = Delta(y0, y);

                    auto gaussian = gauss_matrix[delta_x][delta_y];

                    accumulation_red += matrix.red_chanel[y][x] * gaussian;
                    accumulation_green += matrix.green_chanel[y][x] * gaussian;
                    accumulation_blue += matrix.blue_chanel[y][x] * gaussian;
                }
            }
            new_matrix.red_chanel[y0][x0] = std::clamp<double>(accumulation_red, 0, 1);
            new_matrix.green_chanel[y0][x0] = std::clamp<double>(accumulation_green, 0, 1);
            new_matrix.blue_chanel[y0][x0] = std::clamp<double>(accumulation_blue, 0, 1);
        }
    }
    return new_matrix;
}
}  // namespace

Blur::Blur(double sigma) : sigma_(sigma) {
}

void Blur::Process(Image& input) {
    auto rgb = input.GetNormalChannels();

    auto new_rgb = ApplyGaussian(rgb, input.GetHeight(), input.GetWidth(), sigma_);

    Image result = Image(new_rgb);
    input = result;
}
