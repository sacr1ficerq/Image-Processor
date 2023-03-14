#pragma once

#include "file_management/bmp_file.h"
#include "filters/filter.h"

#include <string>
#include <vector>

namespace parsing {
size_t ParseSize(std::string argument);

double ParsePercent(std::string argument);

double ParsePositiveDouble(std::string argument);

std::string ParseString(std::string argument);

std::string ParseFilterName(char* argument);
}  // namespace parsing

class Controller {
public:
    explicit Controller(int argc, char** argv);

    ~Controller();

    Path GetOutputPath();

    Path GetInputPath();

    void ApplyFilters(Image& img);

    void PrintHelp();

    bool no_arguments = false;

private:
    void ParseFilters(char** argv, size_t last);

    void ParsePaths(char** argv);

    std::vector<Filter*> filters_;

    Path output_path_;
    Path input_path_;
};
