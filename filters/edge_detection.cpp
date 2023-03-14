#include "edge_detection.h"

#include "gray_scale.h"

#include <cmath>

namespace {
static const Matrix EDGE_DETECTION_MATRIX = {std::vector<int8_t>({0, -1, 0}), std::vector<int8_t>({-1, 4, -1}),
                                             std::vector<int8_t>({0, -1, 0})};
}

EdgeDetection::EdgeDetection(double threshold) : Convolution(EDGE_DETECTION_MATRIX), threshold_(std::floor(255*threshold)) {
}

void EdgeDetection::Process(Image& input) {
    GrayScale* gs = new GrayScale();
    gs->Process(input);
    delete gs;
    Convolution::Process(input);
    Basic::Process(input);
}

Color EdgeDetection::Function(const Color& color) {
    Color result{0, 0, 0};
    result.red = color.red > threshold_ ? 255 : 0;
    result.green = color.green > threshold_ ? 255 : 0;
    result.blue = color.blue > threshold_ ? 255 : 0;
    return result;
}