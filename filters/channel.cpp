#include "channel.h"

void GetChannel::Process(Image& image) {
    RGBMatrix matrix = image.GetChannels();
    Channel channel;
    if (type_ == ChannelType::Red) {
        channel = matrix.red_chanel;
    } else if (type_ == ChannelType::Green) {
        channel = matrix.green_chanel;
    } else if (type_ == ChannelType::Blue) {
        channel = matrix.blue_chanel;
    }
    RGBMatrix result{RGBMatrix{channel, channel, channel}};
    image = Image(result);
}

GetChannel::GetChannel(std::string type) {
    if (type == "red") {
        type_ = ChannelType::Red;
    } else if (type == "green") {
        type_ = ChannelType::Green;
    } else if (type == "blue") {
        type_ = ChannelType::Blue;
    } else {
        //        throw IncorrectData();
    }
}
