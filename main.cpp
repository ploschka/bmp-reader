#include <iostream>

#include <bmpreader/reader/BMPReader.hpp>

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cerr << "Usage of " << argv[0] << ":\n"
            << argv[0] << " <filename>\n";
        return 0;
    }

    BMPReader reader;
    int err;
    err = reader.openBMP(argv[1]);
    if (err)
    {
        std::cerr << "Error occured while opening file\n";
        return err;
    }

    err = reader.displayBMP();
    if (err)
    {
        std::cerr << "Error occured while displaying bmp\n";
        return err;
    }

    err = reader.closeBMP();
    if (err)
    {
        std::cerr << "Error occured while closing file\n";
        return err;
    }
    return 0;
}

