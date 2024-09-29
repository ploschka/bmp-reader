#include <bmpreader/structs/Structs.hpp>
#include <cstdint>

BitMapHeader::BitMapHeader(uint32_t _size) : size(_size) {}
BitMapV5Header::BitMapV5Header(uint32_t _size) : BitMapV4Header(_size) {}
BitMapV4Header::BitMapV4Header(uint32_t _size) : BitMapInfoHeader(_size) {}
BitMapInfoHeader::BitMapInfoHeader(uint32_t _size) : BitMapHeader(_size) {}
BitMapCoreHeader::BitMapCoreHeader(uint32_t _size) : BitMapHeader(_size) {}

