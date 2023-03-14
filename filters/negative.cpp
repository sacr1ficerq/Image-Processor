#include "negative.h"

Color Negative::Function(const Color& c) {
    Color result;
    result.red = 255 - c.red;
    result.green = 255 - c.green;
    result.blue = 255 - c.blue;
    return result;
}