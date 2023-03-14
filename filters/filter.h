#pragma once

#include "../image/image.h"

class Filter {
public:
    virtual ~Filter() = default;

    virtual void Process(Image& input) = 0;
};