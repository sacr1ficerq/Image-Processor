#pragma once
#include "filter.h"

class Basic : virtual public Filter {
public:
    void Process(Image& input) override;

protected:
    virtual Color Function(const Color& c) = 0;
};
