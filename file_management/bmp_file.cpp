#include "bmp_file.h"

#include "../my_exception.h"

#include <fstream>
#include <iostream>

InvalidFile invalid_file_bmp;

namespace BMP{
void WriteByte(std::ofstream& output, Byte byte) {
    output.write(reinterpret_cast<char*>(&byte), 1);
}

int32_t GetInt(const std::vector<Byte>& binary_vector, size_t position) {
    size_t sum = 0;
    for (int i = 0; i < 4; ++i) {
        try {
            sum += binary_vector[position + i] << 8 * i;
        } catch (std::exception& e) {
            throw invalid_file_bmp;
        }
    }
    return sum;
}

void WriteInt(std::vector<Byte>& target_vector, size_t pos, int32_t value) {
    for (int i = 0; i < 4; ++i) {
        Byte byte = value % (1 << 8);
        target_vector[pos + i] = byte;
        value -= byte;
        value /= (1 << 8);
    }
}

void WriteColor(std::vector<Byte>& target_vector, size_t pos, Color color) {
    target_vector[pos++] = color.blue;
    target_vector[pos++] = color.green;
    target_vector[pos++] = color.red;
}

Color GetColor(const std::vector<Byte>& binary_vector, size_t pos) {
    try {
        const auto blue = binary_vector[pos];
        const auto green = binary_vector[pos + 1];
        const auto red = binary_vector[pos + 2];

        return Color{red, green, blue};
    } catch (std::exception& e) {
        throw invalid_file_bmp;
    }
}

size_t CalculatePadding(size_t width) {
    return (4 - 3 * width % 4) % 4;
}

Image ReadMatrix(const std::vector<Byte>& bitmap_data, const size_t height, const size_t width) {
    size_t padding = CalculatePadding(width);
    int i = 0;
    Image img(height, width);
    for (int y = static_cast<int>(height) - 1; y > -1; --y) {
        for (int x = 0; x < static_cast<int>(width); ++x) {
            try {
                auto color = GetColor(bitmap_data, i);
                img.SetPixel(x, y, color);
            } catch (std::exception& e) {
                throw invalid_file_bmp;
            }
            i += 3;
        }
        i += padding;
    }
    return img;
}

std::vector<Byte> GetBitmapData(const Image& img) {
    size_t height = img.GetHeight();
    size_t width = img.GetWidth();
    auto matrix = img.GetMatrix();

    size_t padding = CalculatePadding(width);
    std::vector<Byte> result(height * (3 * width + padding), 0);
    size_t i = 0;
    for (int y = static_cast<int>(height) - 1; y > -1; --y) {
        for (int x = 0; x < static_cast<int>(width); ++x) {
            try {
                Color color = matrix[y][x];
                WriteColor(result, i, color);
            } catch (std::exception& e) {
                throw invalid_file_bmp;
            }
            i += 3;
        }
        i += padding;
    }
    return result;
}

void SaveBMP(const std::vector<Byte>& header, const std::vector<Byte>& bitmap_data, const Path& output_path) {
    std::ofstream out(output_path, std::ios::binary);

    if (!out) {
        throw invalid_file_bmp;
    }

    for (const auto& byte : header) {
        WriteByte(out, byte);
    }

    for (const auto& byte : bitmap_data) {
        WriteByte(out, byte);
    }
}

std::vector<Byte> GenerateHeader(size_t image_width, size_t image_height, size_t bitmap_data_size) {
    auto header = std::vector<Byte>(54);
    // ID
    header[0] = 'B';
    header[1] = 'M';
    // Offset where the pixel array (bitmap data) can be found
    header[10] = 54;
    // Number of bytes in the DIB header (from this point)
    header[14] = 40;
    // Number of color planes being used
    header[26] = 1;
    // Number of bits per pixel
    header[28] = 24;
    // Print resolution of the image
    header[38] = 0;
    header[39] = 35;
    header[40] = 46;
    header[41] = 0;
    header[42] = 0;
    header[43] = 35;
    header[44] = 46;
    header[45] = 0;
    // Size of the BMP file (54 bytes header + n bytes data)
    WriteInt(header, 2, 54 + bitmap_data_size);
    // Width of the bitmap in pixels
    WriteInt(header, 18, image_width);
    // Height of the bitmap in pixels. Positive for bottom to top pixel order.
    WriteInt(header, 22, image_height);
    // Size of the raw bitmap data (including padding)
    WriteInt(header, 34, bitmap_data_size);

    return header;
}

bool ValidateHeader(const std::vector<Byte>& header) {
        // ID
        if (header[0] != 'B'|| header[1] != 'M'){
            std::cout << "invalid ID" << std::endl;
            throw invalid_file_bmp;
        }
        // Offset where the pixel array (bitmap data) can be found
        if (header[10] != 54){
            std::cout << "invalid offset" << std::endl;
            throw invalid_file_bmp;
        }
        // Number of bytes in the DIB header (from this point)
        if (header[14] != 40){
            std::cout << "invalid DIB size" << std::endl;
            throw invalid_file_bmp;
        }
        // Number of color planes being used
        if (header[26] != 1){
            std::cout << "invalid pallet size" << std::endl;
            throw invalid_file_bmp;
        }
        // Number of bits per pixel
        if (header[28] != 24){
            std::cout << "invalid bits per pixel" << std::endl;
            throw invalid_file_bmp;
        }
        // Size of the BMP file (54 bytes header + 16 bytes data)
        auto bitmap_data_size_1 = GetInt(header, 2) - 54;
        // Width of the bitmap in pixels
        auto image_width = GetInt(header, 18);
        // Height of the bitmap in pixels. Positive for bottom to top pixel order.
        auto image_height = GetInt(header, 22);
        // Size of the raw bitmap data (including padding)
        auto bitmap_data_size_2 = GetInt(header, 34);
        if (bitmap_data_size_1 != bitmap_data_size_2){
            std::cout << "invalid bitmap size" << std::endl;
            throw invalid_file_bmp;
        }
        if (bitmap_data_size_1 != image_height * static_cast<size_t>(3 * image_width + CalculatePadding(image_width))){
            std::cout << "invalid bitmap size" << std::endl;
            throw invalid_file_bmp;
        }
        if (image_width == 0 || image_height == 0){
            throw invalid_file_bmp;
        }
        return true;
    }

std::vector<Byte> ReadHeader(std::ifstream& input) {
    static const size_t HEADER_SIZE = 54;
    std::vector<Byte> result = std::vector<Byte>(HEADER_SIZE);
    try {
        input.read(reinterpret_cast<char*>(result.data()), HEADER_SIZE);
    } catch (std::exception& e) {
        throw invalid_file_bmp;
    }
    ValidateHeader(result);
    return result;
}

std::vector<Byte> ReadBitmap(std::ifstream& input, size_t bitmap_size) {
    std::vector<Byte> result = std::vector<Byte>(bitmap_size);
    try {
        input.read(reinterpret_cast<char*>(result.data()), bitmap_size);
    } catch (std::exception& e) {
        throw invalid_file_bmp;
    }
    return result;
}
}  // namespace

Image BMPFile::Load(const Path& path) {
    std::ifstream input(path, std::ios::binary);

    if (!input) {
        throw invalid_file_bmp;
    }

    auto header = BMP::ReadHeader(input);
    size_t width = BMP::GetInt(header, 18);
    size_t height = BMP::GetInt(header, 22);

    auto padding = BMP::CalculatePadding(width);

    auto bitmap_size = static_cast<std::streamsize>((width * 3 + padding) * height);
    auto bitmap_data = BMP::ReadBitmap(input, bitmap_size);

    return BMP::ReadMatrix(bitmap_data, height, width);
}

void BMPFile::Save(const Image& img, const Path& output_path) {
    auto bitmap_data = BMP::GetBitmapData(img);
    const auto header = BMP::GenerateHeader(img.GetWidth(), img.GetHeight(), bitmap_data.size());

    BMP::SaveBMP(header, bitmap_data, output_path);
}
