#include "threshold.h"

#include <cmath>

Threshold::Threshold(double threshold) : threshold_(static_cast<Byte>(std::floor(threshold*255))) {
}

Color Threshold::Function(const Color &c) {
    auto sum = c.red + c.green + c.blue;
    auto black = Color{0, 0, 0};
    auto white = Color{255, 255, 255};
    return sum > threshold_ ? white : black;
}