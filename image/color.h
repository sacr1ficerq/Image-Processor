#pragma once

#include <cstdint>

using Byte = uint8_t;
using Degree = double;


struct HSL{
    Degree hue = 0;
    double saturation = 0;
    double lightness = 0;
};

struct HSV{
    Degree hue = 0;
    double saturation = 0;
    double value = 0;

    bool operator==(HSV other) const;
};

struct NormalColor{
    double red = 0;
    double green = 0;
    double blue = 0;
};

class Color {
public:
    Color() = default;
    Color(Byte red, Byte green, Byte blue);
    Color(const HSL& hsl);
    Color(const NormalColor& normal);
    Color(const HSV& hsv);

    Byte red = 0;
    Byte green = 0;
    Byte blue = 0;

    HSV GetHSV() const;
    HSL GetHSL() const;
    NormalColor GetNormal() const;

    bool operator==(Color other) const;
};