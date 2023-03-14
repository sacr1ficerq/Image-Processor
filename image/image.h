#pragma once

#include "color.h"

#include <cstdint>
#include <functional>
#include <vector>

using Matrix = std::vector<std::vector<int8_t>>;
using Channel = std::vector<std::vector<Byte>>;
using NormalChannel = std::vector<std::vector<double>>;

struct NormalRGBMatrix {
    NormalChannel red_chanel;
    NormalChannel green_chanel;
    NormalChannel blue_chanel;
};

struct RGBMatrix {
    Channel red_chanel;
    Channel green_chanel;
    Channel blue_chanel;
};

using ImageMatrix = std::vector<std::vector<Color>>;

class Image {
public:
    Image() = default;

    Image(size_t height, size_t width);

    Image(const RGBMatrix& rgb_matrix);

    Image(const NormalRGBMatrix& normal_rgb_matrix);

    Image(const ImageMatrix& new_image_matrix);

    NormalRGBMatrix GetNormalChannels() const;

    RGBMatrix GetChannels() const;

    size_t GetHeight() const;
    size_t GetWidth() const;

    ImageMatrix GetMatrix() const;

    const Color GetPixel(size_t x, size_t y) const;
    void SetPixel(size_t x, size_t y, Color color);

private:
    ImageMatrix image_matrix_;
};
