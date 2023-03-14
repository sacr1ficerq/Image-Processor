#include "intensity.h"

Intensity::Intensity(double coefficient) : coefficient_(coefficient) {
}

Color Intensity::Function(const Color& c) {
    HSV hsv = c.GetHSV();
    hsv.value = std::clamp<double>(hsv.value * coefficient_, 0, 1);
    return Color(hsv);
}