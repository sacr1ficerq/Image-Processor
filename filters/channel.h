#pragma once

#include <string>

#include "filter.h"

enum class ChannelType { Red, Green, Blue };

class GetChannel : public Filter {
public:
    GetChannel(std::string type);
    void Process(Image& image) override;

private:
    ChannelType type_;
};
