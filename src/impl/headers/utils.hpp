#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/core/mat.hpp>

namespace utils
{

/**
 * @brief Reverse the bits of an uchar (ex : 164(d) <=> 10100100(b) to 00100101(b) <=> 37(d) )
 * @param u : the uchar to reverse
 * @return an uchar with the bits of u reversed
 */
uchar reverseUcharBits(uchar u);

/**
 * @brief Compute the morton code of a 3*8 bits color (interleaving the 24 bits into an unsigned int)
 * @param bgr : the input color
 * @return the morton code of the input color
 */
unsigned int getColorMortonCode(const cv::Vec3b& bgr);

/**
 * @brief Create a color palette to show quantization on
 * @param widthHeight the width/height of the image
 * @return a palette image
 */
cv::Mat getDemoPaletteImage(const int widthHeight);

}

#endif // UTILS_HPP
