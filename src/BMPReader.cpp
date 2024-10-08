#include <cstdint>
#include <iostream>
#include <memory>
#include <new>

#include <bmpreader/reader/BMPReader.hpp>

static char getChar(const RGBTriple& _triple)
{
    if (_triple.blue == 255 &&
        _triple.green == 255 &&
        _triple.red == 255)
    {
        return ' ';
    }
    else
    {
        return '#';
    }
}

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

const char* BMPReader::initV5Header(const char* _buffer)
{
    _buffer = initV4Header(_buffer);
    // Do V5 parsing
    auto h = dynamic_cast<BitMapV5Header*>(infoHeader.get());

    h->bV5Intent = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV5ProfileData = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV5ProfileSize = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV5Reserved = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    return _buffer;
}

const char* BMPReader::initV4Header(const char* _buffer)
{
    _buffer = initInfoHeader(_buffer);
    // Do V4 parsing
    auto h = dynamic_cast<BitMapV4Header*>(infoHeader.get());

    h->bV4RedMask = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV4GreenMask = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV4BlueMask = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV4AlphaMask = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV4CSType = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    // Currently not initializing bV4Endpoints
    _buffer += sizeof(h->bV4Endpoints);

    h->bV4GammaRed = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV4GammaGreen = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->bV4GammaBlue = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    return _buffer;
}

const char* BMPReader::initInfoHeader(const char* _buffer)
{
    // Do Info parsing
    auto h = dynamic_cast<BitMapInfoHeader*>(infoHeader.get());

    h->biWidth = *reinterpret_cast<const int32_t*>(_buffer);
    _buffer += sizeof(const int32_t);

    h->biHeight = *reinterpret_cast<const int32_t*>(_buffer);
    _buffer += sizeof(const int32_t);

    h->biPlanes = *reinterpret_cast<const uint16_t*>(_buffer);
    _buffer += sizeof(const uint16_t);

    h->biBitCount = *reinterpret_cast<const uint16_t*>(_buffer);
    _buffer += sizeof(const uint16_t);

    h->biCompression = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->biSizeImage = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->biXPelsPerMeter = *reinterpret_cast<const int32_t*>(_buffer);
    _buffer += sizeof(const int32_t);

    h->biYPelsPerMeter = *reinterpret_cast<const int32_t*>(_buffer);
    _buffer += sizeof(const int32_t);

    h->biClrUsed = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    h->biClrImportant = *reinterpret_cast<const uint32_t*>(_buffer);
    _buffer += sizeof(const uint32_t);

    return _buffer;
}

const char* BMPReader::initCoreHeader(const char* _buffer)
{
    // Do Core parsing
    auto h = dynamic_cast<BitMapCoreHeader*>(infoHeader.get());

    h->bcWidth = *reinterpret_cast<const uint16_t*>(_buffer);
    _buffer += sizeof(const uint16_t);

    h->bcHeight = *reinterpret_cast<const uint16_t*>(_buffer);
    _buffer += sizeof(const uint16_t);

    h->bcPlanes = *reinterpret_cast<const uint16_t*>(_buffer);
    _buffer += sizeof(const uint16_t);

    h->bcBitCount = *reinterpret_cast<const uint16_t*>(_buffer);
    _buffer += sizeof(const uint16_t);

    return _buffer;
}

const char* BMPReader::initInfo(const char* _buff, uint32_t _size)
{
    const char* retbuff;

    switch (_size)
    {
    case BM_V5HeaderSize:
        infoHeader = std::make_unique<BitMapV5Header>(BM_V5HeaderSize);
        retbuff = initV5Header(_buff);
        break;

    case BM_V4HeaderSize:
        infoHeader = std::make_unique<BitMapV4Header>(BM_V4HeaderSize);
        retbuff = initV4Header(_buff);
        break;

    case BM_InfoHeaderSize:
        infoHeader = std::make_unique<BitMapInfoHeader>(BM_InfoHeaderSize);
        retbuff = initInfoHeader(_buff);
        break;

    case BM_CoreHeaderSize:
        infoHeader = std::make_unique<BitMapCoreHeader>(BM_CoreHeaderSize);
        retbuff = initCoreHeader(_buff);
        break;

    default:
        retbuff = nullptr;
        break;
    }
    return retbuff;
}

int BMPReader::openBMP(const std::string& _filename)
{
    const std::size_t bufferSize = BM_FileHeaderSize + BM_V5HeaderSize;
    char buffer[bufferSize];

    file = std::ifstream(_filename, std::ios_base::binary);
    if (file.fail())
    {
        return E_ROPEN;
    }

    file.read(buffer, bufferSize);
    if (file.fail() && !file.eof())
    {
        closeBMP();
        return E_RREAD;
    }
    std::size_t charsRed = file.gcount();

    if (charsRed < BM_FileHeaderSize)
    {
        closeBMP();
        return E_RINVF;
    }

    const char* ptr = buffer;
    ptr = initFileHeader(ptr);
    charsRed -= BM_FileHeaderSize;

    if (fileHeader->type != bitMapSignature)
    {
        closeBMP();
        return E_RSIGN;
    }

    if (charsRed < sizeof(uint32_t))
    {
        closeBMP();
        return E_RINVF;
    }

    uint32_t infoSize = *reinterpret_cast<const uint32_t*>(ptr);
    ptr += sizeof(const uint32_t);

    if (charsRed < infoSize)
    {
        closeBMP();
        return E_RINVF;
    }

    ptr = initInfo(ptr, infoSize);
    if (!ptr)
    {
        closeBMP();
        return E_RSIZE;
    }

    charsRed -= infoSize;

    actualSize = infoHeader->getPictureSize();
    if (actualSize == 0)
    {
        closeBMP();
        return E_RSUPP;
    }

    file.seekg(fileHeader->offset, std::ios_base::beg);
    if (file.fail())
    {
        closeBMP();
        return E_RSEEK;
    }

    return SUCCESS;
}

int BMPReader::displayBMP()
{
    int32_t width = infoHeader->getWidth();
    int32_t height = infoHeader->getHeight();
    std::size_t lineWidth = infoHeader->getLineWidth();

    int result = SUCCESS;
    std::unique_ptr<char[]> image;
    try
    {
        image = std::make_unique<char[]>(actualSize);
    }
    catch (std::bad_alloc& e)
    {
        result = E_RNMEM;
    }
    if (result != SUCCESS)
    {
        closeBMP();
        return result;
    }

    file.read(image.get(), actualSize);
    if (file.fail())
    {
        closeBMP();
        return E_RREAD;
    }
    if (file.eof())
    {
        closeBMP();
        return E_RINVF;
    }

    if (height > 0)
    {
        for (int32_t i = height - 1; i > 0; --i)
        {
            const char* line = image.get() + i * lineWidth;
            const char* pixel = line;

            RGBTriple triple;

            for (int32_t j = 0; j < width; ++j)
            {
                pixel = infoHeader->getPixel(pixel, triple);
                std::cout << getChar(triple);
            }
            std::cout << '\n';
        }
    }
    else
    {
        for (int32_t i = 0; i < std::abs(height); ++i)
        {
            const char* line = image.get() + i * lineWidth;
            const char* pixel = line;

            RGBTriple triple;

            for (int32_t j = 0; j < width; ++j)
            {
                pixel = infoHeader->getPixel(pixel, triple);
                std::cout << getChar(triple);
            }
            std::cout << '\n';
        }
    }

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

