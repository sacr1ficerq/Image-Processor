#include <gtest/gtest.h>

#include <iostream>

#include "../image/color.h"

auto color_rgb = Color(89, 30, 81);

auto color_hsv = HSV{308.0, 0.663, 0.349};
HSV result_hsv = color_rgb.GetHSV();

Color result_rgb = Color(color_hsv);

TEST(RGBtoHSV, valid_input) {
    EXPECT_EQ(result_hsv.hue, color_hsv.hue) << "hue fail" << std::endl;
    EXPECT_EQ(result_hsv.saturation, color_hsv.saturation) << "saturation fail" << std::endl;
    EXPECT_EQ(result_hsv.value, color_hsv.value) << "value fail" << std::endl;
}

TEST(HSVtoRGB, valid_input) {
    EXPECT_EQ(result_rgb.red, color_rgb.red) << "red fail" << std::endl;
    EXPECT_EQ(result_rgb.green, color_rgb.green) << "green fail " << std::endl;
    EXPECT_EQ(result_rgb.blue, color_rgb.blue) << "blue fail" << std::endl;
}
