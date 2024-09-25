#include <cstdint>

struct BitMapFileHeader {
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserverd;
  uint32_t offset;
};

struct BitMapV5Header {
  uint32_t bV5Size;
  int32_t  bV5Width;
  int32_t  bV5Height;
  uint16_t bV5Planes;
  uint16_t bV5BitCount;
  uint32_t bV5Compression;
  uint32_t bV5SizeImage;
  int32_t  bV5XPelsPerMeter;
  int32_t  bV5YPelsPerMeter;
  uint32_t bV5ClrUsed;
  uint32_t bV5ClrImportant;
  uint32_t bV5RedMask;
  uint32_t bV5GreenMask;
  uint32_t bV5BlueMask;
  uint32_t bV5AlphaMask;
  uint32_t bV5CSType;
  uint8_t  bV5Endpoints[36];
  uint32_t bV5GammaRed;
  uint32_t bV5GammaGreen;
  uint32_t bV5GammaBlue;
  uint32_t bV5Intent;
  uint32_t bV5ProfileData;
  uint32_t bV5ProfileSize;
  uint32_t bV5Reserved;
};

struct BitMapV4Header
{
  uint32_t bV4Size;
  int32_t  bV4Width;
  int32_t  bV4Height;
  uint16_t bV4Planes;
  uint16_t bV4BitCount;
  uint32_t bV4V4Compression;
  uint32_t bV4SizeImage;
  int32_t  bV4XPelsPerMeter;
  int32_t  bV4YPelsPerMeter;
  uint32_t bV4ClrUsed;
  uint32_t bV4ClrImportant;
  uint32_t bV4RedMask;
  uint32_t bV4GreenMask;
  uint32_t bV4BlueMask;
  uint32_t bV4AlphaMask;
  uint32_t bV4CSType;
  uint8_t  bV4Endpoints[36];
  uint32_t bV4GammaRed;
  uint32_t bV4GammaGreen;
  uint32_t bV4GammaBlue;
};

struct BitMapInfoHeader
{
  uint32_t biSize;
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
};

struct BitMapCoreHeader
{
  uint32_t bcSize;
  uint16_t bcWidth;
  uint16_t bcHeight;
  uint16_t bcPlanes;
  uint16_t bcBitCount;
};

