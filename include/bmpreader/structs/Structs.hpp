#include <cstdint>

const std::uint16_t bitMapSignature = 0x4d42;

struct BitMapFileHeader
{
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
};
const std::size_t bitMapFileHeaderSize = 14;

struct BitMapHeader
{
    uint32_t size;


    BitMapHeader(uint32_t _size);
    virtual ~BitMapHeader() = default;
};

struct BitMapCoreHeader : public BitMapHeader
{
    uint16_t bcWidth;
    uint16_t bcHeight;
    uint16_t bcPlanes;
    uint16_t bcBitCount;

    BitMapCoreHeader(uint32_t _size);
};
const std::size_t bitMapCoreHeaderSize = 12;

struct BitMapInfoHeader : public BitMapHeader
{
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;

    BitMapInfoHeader(uint32_t _size);
};
const std::size_t bitMapInfoHeaderSize = 40;

struct BitMapV4Header : public BitMapInfoHeader
{
    uint32_t bV4RedMask;
    uint32_t bV4GreenMask;
    uint32_t bV4BlueMask;
    uint32_t bV4AlphaMask;
    uint32_t bV4CSType;
    uint8_t  bV4Endpoints[36];
    uint32_t bV4GammaRed;
    uint32_t bV4GammaGreen;
    uint32_t bV4GammaBlue;

    BitMapV4Header(uint32_t _size);
};
const std::size_t bitMapV4HeaderSize = 108;

struct BitMapV5Header : public BitMapV4Header
{
    uint32_t bV5Intent;
    uint32_t bV5ProfileData;
    uint32_t bV5ProfileSize;
    uint32_t bV5Reserved;

    BitMapV5Header(uint32_t _size);
};
const std::size_t bitMapV5HeaderSize = 124;

