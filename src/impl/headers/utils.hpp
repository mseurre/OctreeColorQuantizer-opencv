#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/core/mat.hpp>

namespace utils
{

/**
 * @brief Compute the morton code of a 3*8 bits color (interleaving the 24 bits into an unsigned int)
 * @param bgr : the input color
 * @return the morton code of the input color
 */
unsigned int getMortonCodeFromColor(const cv::Vec3b& bgr);

/**
 * @brief Compute the color from a morton code (deinterleave 24 bits into 3*8 bits)
 * @param bgr : the input mortonCode
 * @return the color corresponding to the morton code
 */
cv::Vec3b getColorFromMortonCode(const unsigned int mortonCode);

/**
 * @brief Create a demo color palette to show quantization on
 * @param widthHeight the width/height of the image
 * @return a palette image
 */
cv::Mat getDemoPaletteImage(const int widthHeight);

}

#endif // UTILS_HPP
