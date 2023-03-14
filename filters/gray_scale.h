#pragma once

#include "basic.h"

class GrayScale : public Basic {
public:
    Color Function(const Color& input) override;
};
