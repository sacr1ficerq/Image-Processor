cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


add_library(filters_library
        filters/basic.cpp filters/blur.cpp
        filters/convolution.cpp filters/crop.cpp filters/channel.cpp filters/edge_detection.cpp filters/gray_scale.cpp
        filters/negative.cpp filters/saturation.cpp filters/sharpening.cpp filters/sobel.cpp filters/threshold.cpp
        filters/intensity.cpp filters/hue.cpp)

add_library(image_library
        image/image.cpp
        image/color.cpp)


add_executable(image_processor controller.cpp file_management/bmp_file.cpp image_processor.cpp my_exception.cpp my_exception.h)

target_link_libraries(image_processor
        filters_library
        image_library)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tests
        tests/color_tests.cpp
        tests/filter_tests.cpp
        tests/file_management_tests.cpp
        tests/input_tests.cpp
        controller.cpp
        my_exception.cpp)


add_library(
        tests_library
        file_management/bmp_file.cpp)

link_libraries(tests_library
        filters_library)

target_link_libraries(
        tests
        gtest_main
        filters_library
        tests_library
        image_library
)

include(GoogleTest)
gtest_discover_tests(tests)
