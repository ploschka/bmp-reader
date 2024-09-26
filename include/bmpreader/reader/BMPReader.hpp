#pragma once
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
};

class BMPReader
{
private:
    std::ifstream file;
    std::unique_ptr<BitMapFileHeader> fileHeader;
    std::unique_ptr<BitMapHeader> infoHeader;

    const char* initFileHeader(const char* buff);
public:
    BMPReader() = default;
    ~BMPReader();
    int openBMP(const std::string& _filename);
    int displayBMP();
    int closeBMP();
};

