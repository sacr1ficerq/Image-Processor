#include "crop.h"

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
}

void Crop::Process(Image& input) {
    if (height_ == 0 || width_ == 0){
        return;
    }
    height_ = std::min(input.GetHeight(), height_);
    width_ = std::min(input.GetWidth(), width_);
    auto new_image_matrix = ImageMatrix(height_, std::vector<Color>(width_, Color()));
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            new_image_matrix[y][x] = input.GetPixel(x, y);
        }
    }
    input = Image(new_image_matrix);
}
