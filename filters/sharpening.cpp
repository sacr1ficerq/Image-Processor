#include "sharpening.h"
namespace {
static const Matrix SHARPENING_MATRIX = {std::vector<int8_t>({0, -1, 0}), std::vector<int8_t>({-1, 5, -1}),
                                         std::vector<int8_t>({0, -1, 0})};
}

Sharpening::Sharpening() : Convolution(SHARPENING_MATRIX) {
}