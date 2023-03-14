#include "sobel.h"

#include <cmath>

namespace {
void GetAverage(Image& image1, const Image& image2) {
    for (size_t y = 0; y < image1.GetHeight(); ++y) {
        for (size_t x = 0; x < image1.GetWidth(); ++x) {
            Color new_color{0, 0, 0};
            new_color.red = std::hypot(image1.GetPixel(x, y).red, image1.GetPixel(x, y).red);
            new_color.green = std::hypot(image1.GetPixel(x, y).green, image1.GetPixel(x, y).green);
            new_color.blue = std::hypot(image1.GetPixel(x, y).blue, image1.GetPixel(x, y).blue);
            image1.SetPixel(x, y, new_color);
        }
    }
}

static const Matrix VERTICAL_MATRIX = {std::vector<int8_t>({-1, 0, 1}), std::vector<int8_t>({-2, 0, 2}),
                                       std::vector<int8_t>({-1, 0, 1})};

static const Matrix HORIZONTAL_MATRIX = {std::vector<int8_t>({-1, -2, -1}), std::vector<int8_t>({0, 0, 0}),
                                         std::vector<int8_t>({1, 2, 1})};
}  // namespace
Sobel::Sobel(SobelType sobel_type) : sobel_type_(sobel_type) {
}

void Sobel::Process(Image& input) {
    if (sobel_type_ == SobelType::vertical) {
        Convolution vertical(VERTICAL_MATRIX);
        vertical.Process(input);
    } else if (sobel_type_ == SobelType::horizontal) {
        Convolution horizontal(HORIZONTAL_MATRIX);
        horizontal.Process(input);
    } else if (sobel_type_ == SobelType::combined) {
        Convolution vertical(VERTICAL_MATRIX);
        Convolution horizontal(HORIZONTAL_MATRIX);
        vertical.Process(input);
        auto image_copy = input;
        GetAverage(input, image_copy);
    }
}
