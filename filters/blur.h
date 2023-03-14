#pragma once
#include "filter.h"

class Blur : public Filter {
public:
    Blur(double sigma);
    void Process(Image& input) override;

private:
    double sigma_;
};