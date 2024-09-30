#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <memory>

#include <bmpreader/structs/Structs.hpp>

enum ReaderError
{
    SUCCESS = 0,  // No error
    E_ROPEN = -1, // Error opening file
    E_RREAD = -2, // Reading error
    E_RSIGN = -3, // Invalid bmp signature
    E_RINVF = -4, // Invalid bmp file
    E_RCLSE = -5, // Error closing file
    E_RSIZE = -6, // Invalid info header size
    E_RSEEK = -7, // Error while seeking file
    E_RSUPP = -8, // Unsupported bmp file
    E_RNMEM = -9, // Insufficient memory for image data
};

class BMPReader
{
private:
    std::ifstream file;
    std::unique_ptr<BitMapFileHeader> fileHeader;
    std::unique_ptr<BitMapHeader> infoHeader;

    const char* initFileHeader(const char* _buff);
    const char* initInfo(const char* _buff, uint32_t _size);

    const char* initV5Header(const char* _buff);
    const char* initV4Header(const char* _buff);
    const char* initInfoHeader(const char* _buff);
    const char* initCoreHeader(const char* _buff);

    std::size_t actualSize; // Size of the full image in bytes
    std::size_t pixelsPerLine;
public:
    BMPReader() = default;
    ~BMPReader();
    int openBMP(const std::string& _filename);
    int displayBMP();
    int closeBMP();
};

