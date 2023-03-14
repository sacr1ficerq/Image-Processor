#include <gtest/gtest.h>

#include "../controller.h"
#include "../my_exception.h"

char* program_name = ("name");
char* input_file = "inputs/input.bmp";
char* output_file = "test_output.bmp";
char* filter1 = "-gs";
char* filter2 = "-neg";
char* filter3 = "-threshold";
char* param3 = "0.7";
char* filter4 = "-crop";
char* param41 = "609";
char* param42 = "1067";
char* filter5 = "-edge";
char* param5 = "0.56";
char* filter6 = "-sharp";
char* filter7 = "-blur";
char* param7 = "1.6";
char* filter8 = "-saturation";
char* param8 = "0.7";
char* filter9 = "-hue";
char* param9 = "24";
char* filter10 = "-intensity";
char* param11 = "1.5";

std::vector<char*> filters1 = {program_name, input_file, output_file, filter1, filter2, filter3, param3, filter4, param41, param42};
std::vector<char*> filters2 = {program_name, input_file, output_file, filter5, param5, filter6};
std::vector<char*> filters3 = {program_name, input_file, output_file, filter7, param7};
std::vector<char*> filters4 = {program_name, input_file, output_file, filter8, param8, filter9, param9, filter10, param11};
std::vector<char*> filters5 = {program_name};

TEST(Filters, basic){
    auto controller = Controller(10, filters1.data());
    EXPECT_FALSE(controller.no_arguments);
    Image img = BMPFile::Load(input_file);
    EXPECT_NO_THROW(controller.ApplyFilters(img));
}

TEST(Filters, matrix){
    auto controller = Controller(6, filters2.data());
    EXPECT_FALSE(controller.no_arguments);
    Image img = BMPFile::Load(input_file);
    EXPECT_NO_THROW(controller.ApplyFilters(img));
}

TEST(Filters, blur){
    auto controller = Controller(5, filters3.data());
    EXPECT_FALSE(controller.no_arguments);
    Image img = BMPFile::Load(input_file);
    EXPECT_NO_THROW(controller.ApplyFilters(img));
}

TEST(Filters, basic2){
    auto controller = Controller(9, filters4.data());
    EXPECT_FALSE(controller.no_arguments);
    Image img = BMPFile::Load(input_file);
    EXPECT_NO_THROW(controller.ApplyFilters(img));
}

TEST(Filters, no_args){
    auto controller = Controller(1, filters5.data());
    EXPECT_TRUE(controller.no_arguments);
}

TEST(Filters, wrong_params){
    char* param = "-0.6";
    filters1[6] = param;
    EXPECT_THROW(Controller(10, filters1.data()), InvalidArgument);
    filters1[6] = param3;
}

TEST(Filters, wrong_filter_name){
    char* filter = "-unknown_filter";
    filters1[4] = filter;
    EXPECT_THROW(Controller(10, filters1.data()), InvalidFilterName);
    filters1[4] = filter1;
}

TEST(Filters, wrong_file_name){
    char* file = "unknown_file.something";
    filters1[1] = file;
    EXPECT_THROW(Controller(10, filters1.data()), InvalidFile);
    filters1[1] = input_file;
}