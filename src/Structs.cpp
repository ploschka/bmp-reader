#include <bmpreader/structs/Structs.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <bit>

BitMapHeader::BitMapHeader(uint32_t _size) : size(_size) {}
BitMapV5Header::BitMapV5Header(uint32_t _size) : BitMapV4Header(_size) {}
BitMapV4Header::BitMapV4Header(uint32_t _size) : BitMapInfoHeader(_size) {}
BitMapInfoHeader::BitMapInfoHeader(uint32_t _size) : BitMapHeader(_size) {}
BitMapCoreHeader::BitMapCoreHeader(uint32_t _size) : BitMapHeader(_size) {}

static const uint16_t supported[] = {24, 32};
static bool isSupported(uint16_t _size)
{
    for (uint16_t i : supported)
    {
        if (i == _size)
            return true;
    }
    return false;
}

static std::size_t padLine(std::size_t _lineWidth)
{
    auto rem = _lineWidth % 4;
    return _lineWidth += rem;
}

std::size_t BitMapCoreHeader::getPictureSize()
{
    if (!isSupported(bcBitCount))
        return 0;

    return getLineWidth() * bcHeight;
}

std::size_t BitMapInfoHeader::getPictureSize()
{
    if (!isSupported(biBitCount))
        return 0;

    return getLineWidth() * std::abs(biHeight);
}

int32_t BitMapCoreHeader::getWidth()
{
    return bcWidth;
}

int32_t BitMapCoreHeader::getHeight()
{
    return bcHeight;
}

int32_t BitMapInfoHeader::getWidth()
{
    return biWidth;
}

int32_t BitMapInfoHeader::getHeight()
{
    return biHeight;
}

std::size_t BitMapCoreHeader::getLineWidth()
{
    std::size_t lineWidth;
    if (bcBitCount < 8)
    {
        lineWidth = bcBitCount * bcWidth;
        auto rem = lineWidth % 8;
        lineWidth /= 8;
        if (rem > 0)
            ++lineWidth;
    }
    else
    {
        lineWidth = bcBitCount / 8 * bcWidth;
    }
    return padLine(lineWidth);
}

std::size_t BitMapInfoHeader::getLineWidth()
{
    std::size_t lineWidth;
    if (biBitCount < 8)
    {
        lineWidth = biBitCount * biWidth;
        auto rem = lineWidth % 8;
        lineWidth /= 8;
        if (rem > 0)
            ++lineWidth;
    }
    else
    {
        lineWidth = biBitCount / 8 * biWidth;
    }
    return padLine(lineWidth);
}

const char* BitMapCoreHeader::getPixel(const char* _pixel, RGBTriple& _triple)
{
    switch (bcBitCount)
    {
    case 24:
        memcpy(&_triple, _pixel, 3);
        _pixel += 3;
        break;
    
    case 32:
        memcpy(&_triple, _pixel, 3);
        _pixel += 4;
        break;
    }

    return _pixel;
}

const char* BitMapInfoHeader::getPixel(const char* _pixel, RGBTriple& _triple)
{
    switch (biBitCount)
    {
    case 24:
        memcpy(&_triple, _pixel, 3);
        _pixel += 3;
        break;
    
    case 32:
        memcpy(&_triple, _pixel, 3);
        _pixel += 4;
        break;
    }

    return _pixel;
}

const char* BitMapV4Header::getPixel(const char* _pixel, RGBTriple& _triple)
{
    switch (biBitCount)
    {
    case 24:
        memcpy(&_triple, _pixel, 3);
        _pixel += 3;
        break;
    
    case 32:
        uint32_t pixel;
        memcpy(&pixel, _pixel, 4);
        uint32_t blue = pixel & bV4BlueMask;
        uint32_t green = pixel & bV4GreenMask;
        uint32_t red = pixel & bV4RedMask;

        _triple.blue = blue >> std::countr_zero(bV4BlueMask);
        _triple.green = green >> std::countr_zero(bV4GreenMask);
        _triple.red = red >> std::countr_zero(bV4RedMask);

        _pixel += 4;
        break;
    }

    return _pixel;
}

