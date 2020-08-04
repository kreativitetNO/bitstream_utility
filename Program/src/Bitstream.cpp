#include <Bitstream.h>
#include <cassert>
#include <cstring>
#include <iostream>

Bitstream::Bitstream(uint8_t const* const buffer)
    : buffer_ { *buffer }
{}

uint64_t Bitstream::extract(short const bitCount)
{
    assert(bitCount != 0);
    assert(bitCount <= 64);
    int const startByte = bitIndex_ / 8;
    int const endByte = (bitIndex_ + bitCount - 1) / 8;
    int const size = endByte - startByte + 1;
    uint64_t result;
    std::memcpy(reinterpret_cast<uint8_t*>(&result) + (8 - size), &buffer_ + startByte, size);
    result = swapEndianess(result);
    result >>= 7 - ((bitIndex_ + bitCount - 1) % 8);
    if (bitCount < 64)
    {
        uint64_t const bitmask = ~(~0ULL << bitCount);
        result &= bitmask;
    }
    bitIndex_ += bitCount;
    return result;
}
