#include "impl/headers/octreeColorQuantizer.hpp"
#include "impl/headers/utils.hpp"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int /*argc*/, char** /*argv*/)
{
    const cv::Mat demoPaletteImg = utils::getDemoPaletteImage(600);

    OctreeColorQuantizer octreeColorQuantizer(demoPaletteImg);
    const unsigned long originalPaletteSize = octreeColorQuantizer.getPaletteSize();

    // Make a quantized palette with only 256 colors
    const unsigned int paletteSize = 256;
    octreeColorQuantizer.setPaletteSize(paletteSize);

    // Display quantization result
    cv::Mat originalVsQuantizedAndPalette = cv::Mat::zeros(demoPaletteImg.rows, demoPaletteImg.cols * 3 + 2, demoPaletteImg.type());
    demoPaletteImg.copyTo(originalVsQuantizedAndPalette(cv::Rect({0, 0}, demoPaletteImg.size())));
    octreeColorQuantizer.getQuantizedImage(demoPaletteImg).copyTo(originalVsQuantizedAndPalette(cv::Rect({demoPaletteImg.cols + 1, 0}, demoPaletteImg.size())));

    cv::Mat paletteImg = octreeColorQuantizer.getPaletteImage();
    cv::resize(paletteImg, paletteImg, cv::Size(demoPaletteImg.rows, demoPaletteImg.cols), 0, 0, cv::INTER_NEAREST);
    paletteImg.copyTo(originalVsQuantizedAndPalette(cv::Rect({demoPaletteImg.cols * 2 + 2, 0}, paletteImg.size())));

    cv::imshow("Original (" + std::to_string(originalPaletteSize) + " colors) vs Quantized (" + std::to_string(octreeColorQuantizer.getPaletteSize()) + " colors) - Color Palette", originalVsQuantizedAndPalette);
    cv::waitKey();

    return 0;
}
