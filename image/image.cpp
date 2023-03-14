#include "image.h"

#include <cmath>

Image::Image(size_t height, size_t width) {
    const Color black;
    image_matrix_ = ImageMatrix(height, std::vector<Color>(width, black));
}

Image::Image(const RGBMatrix& rgb_matrix) {
    image_matrix_ =
        ImageMatrix(rgb_matrix.red_chanel.size(), std::vector<Color>(rgb_matrix.red_chanel[0].size(), Color()));

    for (size_t x = 0; x < GetWidth(); ++x) {
        for (size_t y = 0; y < GetHeight(); ++y) {
            image_matrix_[y][x].red = rgb_matrix.red_chanel[y][x];
            image_matrix_[y][x].green = rgb_matrix.green_chanel[y][x];
            image_matrix_[y][x].blue = rgb_matrix.blue_chanel[y][x];
        }
    }
}

Image::Image(const NormalRGBMatrix& normal_rgb_matrix) {
    image_matrix_ = ImageMatrix(normal_rgb_matrix.red_chanel.size(),
                                std::vector<Color>(normal_rgb_matrix.red_chanel[0].size(), Color{0, 0, 0}));

    for (size_t x = 0; x < GetWidth(); ++x) {
        for (size_t y = 0; y < GetHeight(); ++y) {
            image_matrix_[y][x].red = std::floor(normal_rgb_matrix.red_chanel[y][x] * 255);
            image_matrix_[y][x].green = std::floor(normal_rgb_matrix.green_chanel[y][x] * 255);
            image_matrix_[y][x].blue = std::floor(normal_rgb_matrix.blue_chanel[y][x] * 255);
        }
    }
}

Image::Image(const ImageMatrix& new_image_matrix) {
    image_matrix_ = new_image_matrix;
}

NormalRGBMatrix Image::GetNormalChannels() const {
    NormalChannel red_chanel(GetHeight(), std::vector<double>(GetWidth(), 0));
    NormalChannel green_chanel(GetHeight(), std::vector<double>(GetWidth(), 0));
    NormalChannel blue_chanel(GetHeight(), std::vector<double>(GetWidth(), 0));

    for (size_t x = 0; x < GetWidth(); ++x) {
        for (size_t y = 0; y < GetHeight(); ++y) {
            red_chanel[y][x] = static_cast<double>(image_matrix_[y][x].red) / 255;
            green_chanel[y][x] = static_cast<double>(image_matrix_[y][x].green) / 255;
            blue_chanel[y][x] = static_cast<double>(image_matrix_[y][x].blue) / 255;
        }
    }
    return {red_chanel, green_chanel, blue_chanel};
}

RGBMatrix Image::GetChannels() const {
    Channel red_chanel(GetHeight(), std::vector<Byte>(GetWidth()));
    Channel green_chanel(GetHeight(), std::vector<Byte>(GetWidth()));
    Channel blue_chanel(GetHeight(), std::vector<Byte>(GetWidth()));

    for (size_t x = 0; x < GetWidth(); ++x) {
        for (size_t y = 0; y < GetHeight(); ++y) {
            red_chanel[y][x] = image_matrix_[y][x].red;
            green_chanel[y][x] = image_matrix_[y][x].green;
            blue_chanel[y][x] = image_matrix_[y][x].blue;
        }
    }
    return {red_chanel, green_chanel, blue_chanel};
}

size_t Image::GetHeight() const {
    return image_matrix_.size();
}

size_t Image::GetWidth() const {
    if (image_matrix_.empty()) {
        return 0;
    }
    return image_matrix_[0].size();
}

ImageMatrix Image::GetMatrix() const {
    return image_matrix_;
}

const Color Image::GetPixel(size_t x, size_t y) const {
    return image_matrix_[y][x];
}

void Image::SetPixel(size_t x, size_t y, Color color) {
    image_matrix_[y][x] = color;
}
