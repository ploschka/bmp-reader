#include <bmp/reader/BMPReader.hpp>
#include <iostream>

int BMPReader::openBMP(const std::string& _filename)
{
    file = std::ifstream(_filename, std::ios_base::binary);
    return file.fail();
}

int BMPReader::displayBMP()
{
    std::cout << "Hello, World!\n";
    return std::cout.fail();
}

int BMPReader::closeBMP()
{
    file.close();
    return file.fail();
}

