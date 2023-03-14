#pragma once

#include "filter.h"

class Convolution : virtual public Filter {
public:
    Convolution(Matrix convolution_matrix);

    void Process(Image& input) override;

protected:
    Matrix convolution_matrix_;
};
