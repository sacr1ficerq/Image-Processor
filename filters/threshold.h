#pragma once

#include "basic.h"
class Threshold : public Basic {
public:
    Threshold(double threshold);
    Color Function(const Color& c) override;

private:
    Byte threshold_;
};
