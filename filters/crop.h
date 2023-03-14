#pragma once

#include "filter.h"

class Crop : public Filter {
public:
    Crop(size_t height, size_t width);

    void Process(Image& input) override;

private:
    size_t height_;
    size_t width_;
};