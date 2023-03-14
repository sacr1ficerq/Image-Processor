#include "color.h"

#include <algorithm>
#include <cmath>

namespace {
double Module(double a, int d) {
    if (a < 0) {
        return Module(a + d, d);
    }
    if (a > d) {
        return Module(a - d, d);
    } else {
        return a;
    }
}
}  // namespace

Color::Color(Byte red, Byte green, Byte blue) : red(red), green(green), blue(blue) {
}

Color::Color(const NormalColor& normal) {
    Color result;
    result.red = std::clamp<Byte>(std::round(normal.red * 255), 0, 255);
    result.green = std::clamp<Byte>(std::round(normal.green * 255), 0, 255);
    result.blue = std::clamp<Byte>(std::round(normal.blue * 255), 0, 255);
    *this = result;
}

Color::Color(const HSL& hsl) {
    auto C = (1 - std::abs(2 * hsl.lightness - 1)) * hsl.saturation;
    auto X = C * (1 - (std::abs(static_cast<int>(std::round(hsl.hue / 60)) % 2 - 1)));
    auto m = hsl.lightness - C * 2;

    NormalColor normal_result;
    if (hsl.hue <= 60) {
        normal_result = {C, X, 0};
    } else if (hsl.hue <= 120) {
        normal_result = {X, C, 0};
    } else if (hsl.hue <= 180) {
        normal_result = {0, C, X};
    } else if (hsl.hue <= 240) {
        normal_result = {0, X, C};
    } else if (hsl.hue <= 300) {
        normal_result = {X, 0, C};
    } else if (hsl.hue <= 360) {
        normal_result = {C, 0, X};
    }

    normal_result.red += m;
    normal_result.green += m;
    normal_result.blue += m;

    *this = Color(normal_result);
}

Color::Color(const HSV& hsv) {
    auto C = hsv.value * hsv.saturation;
    auto r = Module(hsv.hue / 60, 2);
    auto X = C * (1 - (std::abs(r - 1)));
    auto m = hsv.value - C;

    NormalColor normal_result;
    if (hsv.hue <= 60) {
        normal_result = {C, X, 0};
    } else if (hsv.hue <= 120) {
        normal_result = {X, C, 0};
    } else if (hsv.hue <= 180) {
        normal_result = {0, C, X};
    } else if (hsv.hue <= 240) {
        normal_result = {0, X, C};
    } else if (hsv.hue <= 300) {
        normal_result = {X, 0, C};
    } else if (hsv.hue <= 360) {
        normal_result = {C, 0, X};
    }

    normal_result.red = std::clamp<double>(normal_result.red + m, 0, 1);
    normal_result.green = std::clamp<double>(normal_result.green + m, 0, 1);
    normal_result.blue = std::clamp<double>(normal_result.blue + m, 0, 1);

    Color result = Color(normal_result);
    *this = result;
}

HSL Color::GetHSL() const {
    auto normal = GetNormal();

    auto cmax = std::max({normal.red, normal.green, normal.blue});
    auto cmin = std::min({normal.red, normal.green, normal.blue});


    auto delta = cmax - cmin;

    Degree H = 0;
    if (delta == 0) {
        H = 0;
    } else if (cmax == normal.red) {
        H = 60 * static_cast<int>(std::ceil((normal.green - normal.blue) / delta)) % 6;
    } else if (cmax == normal.green) {
        H = 60 * ((normal.blue - normal.red) / delta + 2);
    } else if (cmax == normal.blue) {
        H = 60 * ((normal.red - normal.green) / delta + 4);
    }

    Degree L = (cmax - cmin) / 2;

    Degree S;
    if (delta == 0) {
        S = 0;
    } else {
        S = delta / (1 - std::abs(2 * L - 1));
    }

    return HSL{H, S, L};
}

NormalColor Color::GetNormal() const {
    double normal_red = static_cast<double>(red) / 255;
    double normal_green = static_cast<double>(green) / 255;
    double normal_blue = static_cast<double>(blue) / 255;
    return NormalColor{normal_red, normal_green, normal_blue};
}

HSV Color::GetHSV() const {
    auto normal = GetNormal();

    auto cmax = std::max({normal.red, normal.green, normal.blue});
    auto cmin = std::min({normal.red, normal.green, normal.blue});

    auto delta = cmax - cmin;

    Degree H = 0;
    if (delta == 0) {
        H = 0;
    } else if (cmax == normal.red) {
        auto d = normal.green - normal.blue;
        auto m = d / delta;
        m = Module(m, 6);
        H = std::round(60 * m);
    } else if (cmax == normal.green) {
        H = 60 * ((normal.blue - normal.red) / delta + 2);
    } else if (cmax == normal.blue) {
        H = 60 * ((normal.red - normal.green) / delta + 4);
    }
    H = Module(H, 360);

    double V = std::round(cmax * 1000) / 1000;

    Degree S;
    if (delta == 0) {
        S = 0;
    } else {
        S = std::clamp<double>(delta / cmax, 0, 1);
        S = std::round(S * 1000) / 1000;
    }

    return HSV{H, S, V};
    }

bool Color::operator==(Color other) const{
    return (red == other.red && green == other.green && blue == other.blue);
}

bool HSV::operator==(HSV other) const{
    return (hue == other.hue) && (saturation == other.saturation) && (value == other.value);
}
