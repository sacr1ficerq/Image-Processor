#pragma once

#include "basic.h"
#include "convolution.h"

class EdgeDetection : public Convolution, public Basic {
public:
    EdgeDetection(double threshold);

    Color Function(const Color& color) override;

    void Process(Image& input) override;

private:
    Byte threshold_;
};
