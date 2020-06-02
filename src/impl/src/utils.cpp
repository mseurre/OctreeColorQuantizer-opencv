#include "utils.hpp"

namespace utils
{

unsigned int getMortonCodeFromColor(const cv::Vec3b& bgr)
{
    unsigned int mortonCode = 0;

    for (uchar i = 0; i < 8; i++)
        mortonCode |= ((((bgr[0] >> i) & 0b1) << 2) | (((bgr[1] >> i) & 0b1) << 1) | (((bgr[2] >> i) & 0b1))) << 3 * i;

    return mortonCode;
}

cv::Vec3b getColorFromMortonCode(const unsigned int mortonCode)
{
    uchar b = 0, g = 0, r = 0;

    for (uchar i = 0; i < 8; i++)
    {
        b |= ((mortonCode >> (i * 3 + 2)) & 0b1) << i;
        g |= ((mortonCode >> (i * 3 + 1)) & 0b1) << i;
        r |= ((mortonCode >> (i * 3)) & 0b1) << i;
    }

    return cv::Vec3b(b, g, r);
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
            colorPalette.at<cv::Vec3b>(0, i + (widthHeight / keyHues.size()) * c) = interpolatedHue;
        }
    }

    // Extrapolate vertically color -> white
    for (int j = 1; j < widthHeight; j++)
    {
        for (int i = 0; i < widthHeight; i++)
            colorPalette.at<cv::Vec3b>(j, i) = (1.f - static_cast<float>(j) / (widthHeight)) * colorPalette.at<cv::Vec3b>(0, i) + (static_cast<float>(j) / (widthHeight)) * cv::Vec3b(255, 255, 255);
    }

    return colorPalette;
}

}
