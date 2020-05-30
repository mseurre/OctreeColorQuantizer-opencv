#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/core/matx.hpp>

namespace utils
{

uchar reverseUcharBits(uchar u);
unsigned int getColorMortonCode(const cv::Vec3b& bgr);

}

#endif // UTILS_HPP
