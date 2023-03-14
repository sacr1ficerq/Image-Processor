#pragma once

#include "basic.h"

class Intensity : public Basic{
public:
    Intensity(double coefficient);
    Color Function(const Color& c) override;
private:
    double coefficient_;
};