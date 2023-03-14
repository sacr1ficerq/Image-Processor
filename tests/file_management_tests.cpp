#include <gtest/gtest.h>

#include "../file_management/bmp_file.h"
#include "../my_exception.h"

const auto WIDTH = 850;
const auto HEIGHT = 342;
auto padding = BMP::CalculatePadding(WIDTH);
auto bitmap_data_size = HEIGHT * (3 * WIDTH + padding);
auto header = BMP::GenerateHeader(WIDTH, HEIGHT, bitmap_data_size);
std::vector<Byte> BITMAP(bitmap_data_size);
const Color COLOR{255, 200, 100};
const auto VALUE= 2323;

TEST(BMP_reading, headerIO) {
    EXPECT_TRUE(BMP::ValidateHeader(header)) << "Header validation fail" << std::endl;
    BMP::WriteInt(header, 1, 2323);
    EXPECT_THROW(BMP::ValidateHeader(header), InvalidFile)<< "Header validation fail" << std::endl;
}

TEST(BMP_reading, ColorsIO) {
    BMP::WriteColor(BITMAP, 0, COLOR);
    auto color = BMP::GetColor(BITMAP, 0);
    EXPECT_EQ(COLOR, color);
}

TEST(BMP_reading, IntsIO) {
    auto new_header = header;
    BMP::WriteInt(new_header, 1, VALUE);
    auto value = BMP::GetInt(header, 1);
    EXPECT_EQ(VALUE, value);
}

TEST(BMP_reading, ImageMatrixIO) {
    Image img = BMP::ReadMatrix(BITMAP, HEIGHT, WIDTH);
    EXPECT_EQ(BITMAP, BMP::GetBitmapData(img));
    auto old_bitmap= BITMAP;
    BMP::WriteInt(BITMAP, 4, VALUE);
    EXPECT_NE(BMP::GetBitmapData(img), BITMAP);
    EXPECT_EQ(BMP::GetBitmapData(img), old_bitmap);
}
