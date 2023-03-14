#include "hue.h"

Hue::Hue(int degrees) : degrees_(degrees) {
}

Color Hue::Function(const Color& color) {
    auto hsv = color.GetHSV();
    hsv.hue = (static_cast<int>(hsv.hue) + degrees_) % 360;
    return Color(hsv);
}
