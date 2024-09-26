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
    const char* initCoreheader(const char* _buff);
public:
    BMPReader() = default;
    ~BMPReader();
    int openBMP(const std::string& _filename);
    int displayBMP();
    int closeBMP();
};

