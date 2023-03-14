#include <chrono>
#include <iostream>

#include "controller.h"
#include "my_exception.h"

int main(int argc, char** argv) {
    std::cout << "program started" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    try {
        auto controller = Controller(argc, argv);
        if (controller.no_arguments) {
            return 0;
        }

        auto output_path = controller.GetOutputPath();
        auto input_path = controller.GetInputPath();

        Image img = BMPFile::Load(input_path);
        controller.ApplyFilters(img);
        BMPFile::Save(img, output_path);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto execution_time = duration_cast<std::chrono::seconds>(stop - start).count();

    std::cout << "Program finished in " << execution_time << " seconds";
    return 0;
}