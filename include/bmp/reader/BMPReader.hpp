#pragma once
#include <string>
#include <fstream>

class BMPReader
{
private:
    std::ifstream file;
public:
    int openBMP(const std::string& _filename);
    int displayBMP();
    int closeBMP();
};

