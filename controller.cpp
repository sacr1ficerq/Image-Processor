#include "controller.h"

#include "file_management/bmp_file.h"
#include "filters/blur.h"
#include "filters/channel.h"
#include "filters/crop.h"
#include "filters/edge_detection.h"
#include "filters/gray_scale.h"
#include "filters/hue.h"
#include "filters/intensity.h"
#include "filters/negative.h"
#include "filters/saturation.h"
#include "filters/sharpening.h"
#include "filters/sobel.h"
#include "filters/threshold.h"
#include "image/image.h"
#include "my_exception.h"

#include <cstring>
#include <iostream>

InvalidArgument invalid_argument;
InvalidFilterName invalid_filter_name;
InvalidFile invalid_file;

namespace parsing {
size_t ParseSize(std::string argument) {
    try {
        auto result = std::stoi(argument);
        if (result < 0) {
            throw invalid_argument;
        }
        return result;
    } catch (std::exception& e) {
        throw invalid_argument;
    }
}

double ParsePercent(std::string argument) {
    try {
        double result = std::stof(argument);
        if (result < 0 || result > 1) {
            throw invalid_argument;
        }
        return result;
    } catch (std::exception& e) {
        throw invalid_argument;
    }
}

double ParsePositiveDouble(std::string argument) {
    try {
        double result = std::stof(argument);
        if (result < 0) {
            throw invalid_argument;
        }
        return result;
    } catch (std::exception& e) {
        throw invalid_argument;
    }
}

std::string ParseString(std::string argument) {
    try {
        auto result = argument;
        return result;
    } catch (std::exception& e) {
        throw invalid_argument;
    }
}

std::string ParseFilterName(char* arg) {
    std::string result = arg;
    if (!result.starts_with("-")) {
        throw invalid_filter_name;
    }
    return result;
}

std::string ParseFileName(char* arg) {
    std::string result = arg;
    if (!result.ends_with(".bmp")) {
        throw invalid_file;
    }
    return result;
}
}  // namespace parsing

Controller::Controller(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        no_arguments = true;
    }
    else if (argc == 2) {
        throw invalid_argument;
    } else {
        ParsePaths(argv);
        ParseFilters(argv, argc - 1);
    }
}

Path Controller::GetOutputPath() {
    return output_path_;
}

Path Controller::GetInputPath() {
    return input_path_;
}

void Controller::ApplyFilters(Image& img) {
    for (const auto filter : filters_) {
        filter->Process(img);
    }
}

void Controller::PrintHelp() {
    std::cout << "You called help" << std::endl;
    std::cout << "This is list of filters you can apply:" << std::endl;
    std::cout << "    -gs (applies grayscale)" << std::endl;
    std::cout << "    -negative (applies negative)" << std::endl;
    std::cout << "    -crop [WIDTH] [HEIGHT] (crops image from top left corner to given size" << std::endl;
    std::cout << "    -sharp (applies sharpening)" << std::endl;
    std::cout << "    -edge [THRESHOLD] (detects edges and applies threeshold)" << std::endl;
    std::cout << "    -blur [SIGMA] (applies blur with given intensity)" << std::endl;
    std::cout << "    -sobel [SOBEL_TYPE] (applies sobel operator. You can choose between combined; horizontal; vertical;)" << std::endl;
    std::cout << "    -saturation [INTENSITY] (saturates picture with given intensity)" << std::endl;
    std::cout << "    -intensity [INTENSITY] (increases the true color of each pixel)" << std::endl;
    std::cout << "    -hue [DEGREES] (rotates colors hue for given degrees)" << std::endl;
    std::cout << "    -threshold [THRESHOLD] (applies threshold to image)" << std::endl;
    std::cout << "    -channel [COLOR] (return color channel of image. You can choose between red; green; blue;)" << std::endl;
    std::cout << "You can choose multiple filters. Just use this format:" << std::endl;
    std::cout << "{program_name} {input_path} {output_path} -{filter1} [param1] [param2]... -{filter2} [param1] [param2]..." << std::endl;
}

Controller::~Controller() {
    for (auto filter : filters_) {
        delete filter;
    }
}

void Controller::ParseFilters(char** argv, size_t last) {
    size_t position = 3;
    while (position <= last) {
        std::string filter_name = parsing::ParseFilterName(argv[position]);

        if (filter_name == "-neg") {
            filters_.push_back(new Negative());
        } else if (filter_name == "-gs") {
            filters_.push_back(new GrayScale());
        } else if (filter_name == "-sharp") {
            filters_.push_back(new Sharpening());
        } else if (filter_name == "-crop") {
            if (position == last - 1) {
                throw invalid_argument;
            }
            auto new_width = parsing::ParseSize(argv[++position]);
            auto new_height = parsing::ParseSize(argv[++position]);
            filters_.push_back(new Crop(new_height, new_width));
        } else if (filter_name == "-edge") {
            if (position == last) {
                throw invalid_argument;
            }
            auto threshold = parsing::ParsePercent(argv[++position]);
            filters_.push_back(new EdgeDetection(threshold));
        } else if (filter_name == "-blur") {
            if (position == last) {
                throw invalid_argument;
            }
            double sigma = parsing::ParsePositiveDouble(argv[++position]);
            filters_.push_back(new Blur(sigma));
        } else if (filter_name == "-sobel") {
            if (position == last) {
                throw invalid_argument;
            }
            SobelType sobel_type;
            std::string type = parsing::ParseString(argv[++position]);
            if (type == "vertical") {
                sobel_type = SobelType::vertical;
            } else if (type == "horizontal") {
                sobel_type = SobelType::horizontal;
            } else if (type == "combined") {
                sobel_type = SobelType::combined;
            } else {
                throw invalid_argument;
            }
            filters_.push_back(new Sobel(sobel_type));
        } else if (filter_name == "-threshold") {
            if (position == last) {
                throw invalid_argument;
            }
            auto threshold = parsing::ParsePercent(argv[++position]);
            filters_.push_back(new Threshold(threshold));
        } else if (filter_name == "-saturation") {
            if (position == last) {
                throw invalid_argument;
            }
            double coefficient = parsing::ParsePositiveDouble(argv[++position]);
            filters_.push_back(new Saturation(coefficient));
        } else if (filter_name == "-intensity") {
            if (position == last) {
                throw invalid_argument;
            }
            double coefficient = parsing::ParsePositiveDouble(argv[++position]);
            filters_.push_back(new Intensity(coefficient));
        } else if (filter_name == "-hue") {
            if (position == last) {
                throw invalid_argument;
            }
            double coefficient = parsing::ParsePositiveDouble(argv[++position]);
            filters_.push_back(new Hue(coefficient));
        } else if (filter_name == "-channel") {
            if (position != last) {
                throw invalid_argument;
            }
            std::string type = parsing::ParseString(argv[++position]);
            filters_.push_back(new GetChannel(type));
        } else {
            throw invalid_filter_name;
        }
        ++position;
    }
}

void Controller::ParsePaths(char** argv) {
    input_path_ = parsing::ParseFileName(argv[1]);
    output_path_ = parsing::ParseFileName(argv[2]);
}
