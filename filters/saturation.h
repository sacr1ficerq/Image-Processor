#pragma once

#include "basic.h"

class Saturation : public Basic {
public:
    Saturation(double coefficient);
    Color Function(const Color& c) override;

private:
    double coefficient_;
};
