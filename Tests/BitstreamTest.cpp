#include <gtest/gtest.h>
#include <Bitstream.h>

namespace {
    class BitstreamTest : public ::testing::Test
    {
        public:
        BitstreamTest()
            : bitStream_ { buffer_ }
        {}

        private:
        Bitstream bitStream_;
        uint8_t const buffer_[2] = { 0x80 };
    };

    ::testing::AssertionResult AssertHexEquality(const char* xExpr, const char* yExpr,
                                                 uint64_t xVal, uint64_t yVal)
    {
        if (xVal == yVal)
            return ::testing::AssertionSuccess();

        std::ostringstream xValHex;
        xValHex << std::hex << xVal;

        std::ostringstream yValHex;
        yValHex << std::hex << yVal;

        return ::testing::AssertionFailure() <<
               "Expected equality of these values:\n  " <<
               xExpr << "\n    Which is: " << xValHex.str() << "\n  " <<
               yExpr << "\n    Which is: " << yValHex.str() << "\n";
    }

}

TEST_F(BitstreamTest, Hex80GetFirstBit_Returns0x01)
{
    uint8_t const buffer[100] = { 0x80 };
    Bitstream bitstream { buffer };
    EXPECT_PRED_FORMAT2(AssertHexEquality, bitstream.extract(1), 0x01UL);
}

TEST_F(BitstreamTest, Hex80GetFirstTwoBits_Returns0x02)
{
    uint8_t const buffer[100] = { 0x80 };
    Bitstream bitstream { buffer };
    EXPECT_PRED_FORMAT2(AssertHexEquality, bitstream.extract(2), 0x02UL);
}

TEST_F(BitstreamTest, HexFF80GetFirst9Bits_Returns0x01FF)
{
    uint8_t const buffer[100] = { 0xFF, 0x80 };
    Bitstream bitstream { buffer };
    EXPECT_PRED_FORMAT2(AssertHexEquality, bitstream.extract(9), 0x01FF);
}

TEST_F(BitstreamTest, Hex)
{
    uint8_t const buffer[100] = { 0x10, 0x86, 0x8F, 0x13, 0x55, 0x7D, 0xD5, 0x5F };
    Bitstream bitstream { buffer };
    EXPECT_PRED_FORMAT2(AssertHexEquality, 2, bitstream.extract(5));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 0, bitstream.extract(3));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 269, bitstream.extract(9));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 15, bitstream.extract(7));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 9, bitstream.extract(7));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 1, bitstream.extract(1));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 5, bitstream.extract(4));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 1, bitstream.extract(2));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 1, bitstream.extract(2));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 7, bitstream.extract(4));
    EXPECT_PRED_FORMAT2(AssertHexEquality, 27, bitstream.extract(5));
}

TEST(Utility, SwapEndianness_0xFFEEDDCCBBAA9988_returns_0x8899AABBCCDDEEFF)
{
    EXPECT_PRED_FORMAT2(AssertHexEquality, swapEndianess(uint64_t(0xFFEEDDCCBBAA9988UL)), uint64_t(0x8899AABBCCDDEEFFUL));
}

TEST(Utility, SwapEndianness_0xFFEEDDCC_returns_0xCCDDEEFF)
{
    EXPECT_PRED_FORMAT2(AssertHexEquality, swapEndianess(uint32_t(0xFFEEDDCC)), uint32_t(0xCCDDEEFF));
}

TEST(Utility, SwapEndianness_0xFFEE_returns_EEFF)
{
    EXPECT_PRED_FORMAT2(AssertHexEquality, swapEndianess(uint16_t(0xFFEE)), uint16_t(0xEEFFU));
}

TEST(Canary, OneIsOne)
{
    EXPECT_EQ(1, 1);
}