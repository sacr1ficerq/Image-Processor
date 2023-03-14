#include "basic.h"

void Basic::Process(Image& input) {
    for (size_t y = 0; y < input.GetHeight(); ++y) {
        for (size_t x = 0; x < input.GetWidth(); ++x) {
            input.SetPixel(x, y, Function(input.GetPixel(x, y)));
        }
    }
}