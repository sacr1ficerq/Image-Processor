#pragma once

#include "../image/image.h"

#include <cstdint>
#include <string>
#include <vector>

using Path = std::string;

namespace BMP{
    void WriteByte(std::ofstream& output, Byte byte);

    int32_t GetInt(const std::vector<Byte>& binary_vector, size_t position);

    void WriteInt(std::vector<Byte>& target_vector, size_t pos, int32_t value);

    void WriteColor(std::vector<Byte>& target_vector, size_t pos, Color color);

    Color GetColor(const std::vector<Byte>& binary_vector, size_t pos);

    size_t CalculatePadding(size_t width);

    Image ReadMatrix(const std::vector<Byte>& bitmap_data, const size_t height, const size_t width);

    std::vector<Byte> GetBitmapData(const Image& img);

    void SaveBMP(const std::vector<Byte>& header, const std::vector<Byte>& bitmap_data, const Path& output_path);

    std::vector<Byte> GenerateHeader(size_t image_width, size_t image_height, size_t bitmap_data_size);

    bool ValidateHeader(const std::vector<Byte>& header);

    std::vector<Byte> ReadHeader(std::ifstream& input);

    std::vector<Byte> ReadBitmap(std::ifstream& input, size_t bitmap_size);
}  // namespace

struct BMPFile {
public:
    static Image Load(const Path& path);

    static void Save(const Image& img, const Path& output_path);
};