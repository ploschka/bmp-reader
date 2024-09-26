#include <bmpreader/reader/BMPReader.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cerr << "Usage of " << argv[0] << ":\n"
            << argv[0] << " <filename>\n";
        return 0;
    }

    BMPReader reader;
    if (reader.openBMP(argv[1]))
    {
        std::cerr << "Error occured while opening file\n";
        return -1;
    }

    if (reader.displayBMP())
    {
        std::cerr << "Error occured while displaying bmp\n";
        return -1;
    }

    if (reader.closeBMP())
    {
        std::cerr << "Error occured while closing file\n";
        return -1;
    }
    return 0;
}

