#include "gray_scale.h"

Color GrayScale::Function(const Color& c) {
    const Byte new_value = c.red * 0.299 + 0.587 * c.green + 0.114 * c.blue;
    Color result{new_value, new_value, new_value};
    return result;
}
