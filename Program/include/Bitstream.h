#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <cstdint>
#include <cstddef>

class Bitstream
{
    public:
    Bitstream(uint8_t const* const buffer);
    uint64_t extract(short const bitCount);

    private:
    int bitIndex_ { 0 };
    uint8_t const&  buffer_;
};

template <typename T>
inline auto swapEndianess(T const input)
{
    T result = 0;
    uint8_t const* const byteReadPtr = reinterpret_cast<uint8_t const* const>(&input);
    uint8_t* byteWritePtr = reinterpret_cast<uint8_t*>(&result);
    for (int i = 0; i < sizeof(T); ++i)
    {
        byteWritePtr[i] = byteReadPtr[sizeof(T) - (i + 1)];
    }
    return result;
}

#endif