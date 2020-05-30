#include "utils.hpp"

namespace utils
{

uchar reverseUcharBits(uchar u)
{
    u = u >> 4 | u << 4;
    u = (u & 0b11001100) >> 2 | (u & 0b00110011) << 2;
    u = (u & 0b10101010) >> 1 | (u & 0b01010101) << 1;
    return u;
}

unsigned int getColorMortonCode(const cv::Vec3b& bgr)
{
    unsigned int mortonCode = 0;

    // Invert the bits of each color to be able to read the morton code from left to right
    const unsigned int revB = reverseUcharBits(bgr[0]);
    const unsigned int revG = reverseUcharBits(bgr[1]);
    const unsigned int revR = reverseUcharBits(bgr[2]);

    for (uchar i = 0; i < 8; i++)
        mortonCode |= (((revB >> i & 0b1) << 2) | ((revG >> i & 0b1) << 1) | ((revR >> i & 0b1))) << 3 * i;

    return mortonCode;
}

}
