#include <cstdint>
#include <iostream>

#include <bmpreader/reader/BMPReader.hpp>
#include <memory>

BMPReader::~BMPReader()
{
    closeBMP();
}

const char* BMPReader::initFileHeader(const char* _buff)
{
    fileHeader = std::make_unique<BitMapFileHeader>();

    fileHeader->type = *reinterpret_cast<const uint16_t*>(_buff);
    _buff += sizeof(uint16_t);

    fileHeader->size = *reinterpret_cast<const uint32_t*>(_buff);
    _buff += sizeof(uint32_t);

    fileHeader->reserved1 = *reinterpret_cast<const uint16_t*>(_buff);
    _buff += sizeof(uint16_t);

    fileHeader->reserved2 = *reinterpret_cast<const uint16_t*>(_buff);
    _buff += sizeof(uint16_t);

    fileHeader->offset = *reinterpret_cast<const uint32_t*>(_buff);
    _buff += sizeof(uint32_t);

    return _buff;
}

const char* BMPReader::initInfo(const char* _buff, uint32_t _size)
{
    const char* retbuff;

    switch (_size)
    {
    case bitMapV5HeaderSize:
        retbuff = initV5Header(_buff);
        break;

    case bitMapV4HeaderSize:
        retbuff = initV4Header(_buff);
        break;

    case bitMapInfoHeaderSize:
        retbuff = initInfoHeader(_buff);
        break;
    case bitMapCoreHeaderSize:
        retbuff = initCoreheader(_buff);
        break;
    default:
        retbuff = nullptr;
        break;
    }
    return retbuff;
}

int BMPReader::openBMP(const std::string& _filename)
{
    const std::size_t bufferSize = 1024;
    char buffer[bufferSize];

    file = std::ifstream(_filename, std::ios_base::binary);
    if (file.fail())
    {
        return E_ROPEN;
    }

    file.read(buffer, bufferSize);
    if (file.fail() && !file.eof())
    {
        return E_RREAD;
    }
    std::size_t charsRed = file.gcount();

    if (charsRed < bitMapFileHeaderSize)
    {
        return E_RINVF;
    }

    const char* ptr = buffer;
    ptr = initFileHeader(ptr);
    charsRed -= bitMapFileHeaderSize;

    if (fileHeader->type != bitMapSignature)
    {
        return E_RSIGN;
    }

    if (charsRed < sizeof(uint32_t))
    {
        return E_RINVF;
    }

    uint32_t infoSize = *reinterpret_cast<const uint32_t*>(ptr);
    if (charsRed < infoSize)
    {
        return E_RINVF;
    }

    ptr = initInfo(ptr, infoSize);
    if (!ptr)
    {
        return E_RSIZE;
    }

    charsRed -= infoSize;

    return SUCCESS;
}

int BMPReader::displayBMP()
{
    std::cout << "Hello, World!\n";
    return SUCCESS;
}

int BMPReader::closeBMP()
{
    fileHeader.reset(nullptr);
    infoHeader.reset(nullptr);

    if (file.is_open())
    {
        file.close();
        if (file.fail())
        {
            return E_RCLSE;
        }
    }

    return SUCCESS;
}

