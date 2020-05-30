#include "impl/headers/octreeColorQuantizer.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    std::array<cv::Vec3b, 6> keyColors =
    {
        cv::Vec3b(0,   0,  255),    // Red
        cv::Vec3b(0,  255, 255),    // Yellow
        cv::Vec3b(0,  255,  0),     // Green
        cv::Vec3b(255, 255,  0),    // Cyan
        cv::Vec3b(255,  0,   0),    // Blue
        cv::Vec3b(255,  0,  255)    // Magenta
    };

    const unsigned int colorPaletteSize = 100;
    cv::Mat colorPalette(keyColors.size() * colorPaletteSize, keyColors.size() * colorPaletteSize, CV_8UC3);

    // Extrapolate horizontally
    for (uchar c = 0; c < keyColors.size(); c++)
        for (int i = 0; i < colorPaletteSize; i++)
            colorPalette.at<cv::Vec3b>(0, i + colorPaletteSize * c) = (1.f - static_cast<float>(i) / colorPaletteSize) * keyColors[c] +
                    (static_cast<float>(i) / colorPaletteSize) * keyColors[(c + 1) % keyColors.size()];

    // Extrapolate vertically
    for (int i = 1; i < colorPalette.rows; i++)
        for (int j = 0; j < colorPalette.cols; j++)
            colorPalette.at<cv::Vec3b>(i, j) = (1.f - static_cast<float>(i) / 600) * colorPalette.at<cv::Vec3b>(0, j) + (static_cast<float>(i) / 600) * cv::Vec3b(255, 255, 255);

    OctreeColorQuantizer octree(colorPalette);

    const unsigned int paletteSize = 256;
    octree.setPaletteSize(paletteSize);

    cv::Mat originalVsQuantized = cv::Mat::zeros(colorPalette.rows, colorPalette.cols * 2 + 1, colorPalette.type());
    colorPalette.copyTo(originalVsQuantized(cv::Rect({0, 0}, colorPalette.size())));
    octree.getQuantizedImage(colorPalette).copyTo(originalVsQuantized(cv::Rect({colorPalette.cols + 1, 0}, colorPalette.size())));

    cv::imshow("Original vs Quantized to " + std::to_string(paletteSize) + " colors", originalVsQuantized);
    cv::waitKey();

    return 0;
}
