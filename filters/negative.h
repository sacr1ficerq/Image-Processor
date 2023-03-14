#pragma once

#include "basic.h"

class Negative : public Basic {
protected:
    Color Function(const Color& c) override;
};