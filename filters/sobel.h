#pragma once

#include "basic.h"
#include "convolution.h"

enum class SobelType { vertical, horizontal, combined };

class Sobel : public Filter {
public:
    Sobel(SobelType sobel_type);

    void Process(Image& input) override;

private:
    SobelType sobel_type_;
};
