#include <cstdint>

const std::uint16_t bitMapSignature = 0x4d42;

enum BitMapHeaderSize
{
    BM_FileHeaderSize = 14,
    BM_CoreHeaderSize = 12,
    BM_InfoHeaderSize = 40,
    BM_V4HeaderSize = 108,
    BM_V5HeaderSize = 124,
};

struct BitMapFileHeader
{
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
};

struct BitMapHeader
{
    uint32_t size;


    BitMapHeader(uint32_t _size);
    virtual std::size_t getPictureSize() = 0;
    virtual int32_t getWidth() = 0;
    virtual int32_t getHeight() = 0;
    virtual std::size_t getLineWidth() = 0;
    virtual ~BitMapHeader() = default;
};

struct BitMapCoreHeader : public BitMapHeader
{
    uint16_t bcWidth;
    uint16_t bcHeight;
    uint16_t bcPlanes;
    uint16_t bcBitCount;

    BitMapCoreHeader(uint32_t _size);
    std::size_t getPictureSize();
    int32_t getWidth();
    int32_t getHeight();
    std::size_t getLineWidth();
};

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
    std::size_t getPictureSize();
    int32_t getWidth();
    int32_t getHeight();
    std::size_t getLineWidth();
};

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

struct BitMapV5Header : public BitMapV4Header
{
    uint32_t bV5Intent;
    uint32_t bV5ProfileData;
    uint32_t bV5ProfileSize;
    uint32_t bV5Reserved;

    BitMapV5Header(uint32_t _size);
};

