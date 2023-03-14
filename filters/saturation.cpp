#include "saturation.h"

Saturation::Saturation(double coefficient) : coefficient_(coefficient) {
}

Color Saturation::Function(const Color& c) {
    auto hsv = c.GetHSV();
    hsv.saturation = std::clamp<double>(hsv.saturation * coefficient_, 0, 1);
    return Color(hsv);
}
