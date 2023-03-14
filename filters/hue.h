#pragma once

#include "basic.h"

class Hue : public Basic {
public:
    Hue(int degrees);
    Color Function(const Color& color) override;

private:
    int degrees_;
};