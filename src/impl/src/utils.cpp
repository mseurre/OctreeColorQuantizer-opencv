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

cv::Mat getDemoPaletteImage(const int widthHeight)
{
    const std::array<cv::Vec3b, 6> keyHues =
    {
        cv::Vec3b(0,   0,  255),    // Red
        cv::Vec3b(0,  255, 255),    // Yellow
        cv::Vec3b(0,  255,  0),     // Green
        cv::Vec3b(255, 255,  0),    // Cyan
        cv::Vec3b(255,  0,   0),    // Blue
        cv::Vec3b(255,  0,  255)    // Magenta
    };

    cv::Mat colorPalette(widthHeight, widthHeight, CV_8UC3);

    // Extrapolate horizontally in the middle
    for (uchar c = 0; c < keyHues.size(); c++)
    {
        for (float i = 0; i < widthHeight / 6; i++)
        {
            const cv::Vec3b interpolatedHue = (1.f - i / (widthHeight / keyHues.size())) * keyHues[c] + (i / (widthHeight / keyHues.size())) * keyHues[(c + 1) % keyHues.size()];
            colorPalette.at<cv::Vec3b>(widthHeight / 2, i + (widthHeight / keyHues.size()) * c) = interpolatedHue;
        }
    }

    // Extrapolate vertically black -> color -> white
    for (int j = 0; j < widthHeight; j++)
    {
        for (int i = 0; i < widthHeight / 2; i++)
            colorPalette.at<cv::Vec3b>(i, j) = (1.f - static_cast<float>(i) / (widthHeight / 2)) * cv::Vec3b(0, 0, 0) + (static_cast<float>(i) / (widthHeight / 2)) * colorPalette.at<cv::Vec3b>(widthHeight / 2, j);

        for (int i = 0; i < widthHeight / 2; i++)
            colorPalette.at<cv::Vec3b>(i + widthHeight / 2, j) = (1.f - static_cast<float>(i) / (widthHeight / 2)) * colorPalette.at<cv::Vec3b>(widthHeight / 2, j) + (static_cast<float>(i) / (widthHeight / 2)) * cv::Vec3b(255, 255, 255);
    }

    return colorPalette;
}

}
