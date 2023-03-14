#include <gtest/gtest.h>

#include "../controller.h"
#include "../my_exception.h"

TEST(FilterArgument, simple_string) {
    EXPECT_EQ(parsing::ParseString("string example"), "string example") << "string parsing fail" << std::endl;
}

TEST(FilterArgument, size_valid) {
    EXPECT_EQ(parsing::ParseSize("2509"), 2509) << "size parsing fail" << std::endl;
    EXPECT_EQ(parsing::ParseSize("25.09"), 25) << "size parsing fail" << std::endl;
}

TEST(FilterArgument, size_invalid) {
    EXPECT_THROW(parsing::ParseSize("-25"), InvalidArgument) << "size parsing fail" << std::endl;
    EXPECT_THROW(parsing::ParseSize("five"), InvalidArgument) << "size parsing fail" << std::endl;
}

TEST(FilterArgument, percent_valid) {
    EXPECT_FLOAT_EQ(parsing::ParsePercent("0.89"), 0.89) << "percent parsing fail" << std::endl;
    EXPECT_FLOAT_EQ(parsing::ParsePercent("1"), 1) << "percent parsing fail" << std::endl;
}

TEST(FilterArgument, percent_invalid) {
    EXPECT_THROW(parsing::ParsePercent("-0.1"), InvalidArgument) << "percent parsing fail" << std::endl;
    EXPECT_THROW(parsing::ParsePercent("12"), InvalidArgument) << "percent parsing fail" << std::endl;
    EXPECT_THROW(parsing::ParsePercent("point_two"), InvalidArgument) << "percent parsing fail" << std::endl;
}

TEST(FilterName, name_valid) {
    EXPECT_EQ(parsing::ParseFilterName("-saturation"), "-saturation") << "filter name parsing fail" << std::endl;
}
