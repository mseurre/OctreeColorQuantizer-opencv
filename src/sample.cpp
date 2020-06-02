#include "impl/headers/octreeColorQuantizer.hpp"
#include "impl/headers/utils.hpp"

#include <opencv2/highgui.hpp>

int main(int /*argc*/, char** /*argv*/)
{
    const cv::Mat demoPaletteImg = utils::getDemoPaletteImage(600);

    OctreeColorQuantizer octreeColorQuantizer(demoPaletteImg);

    // Make a quantized palette with only 256 colors
    const unsigned int paletteSize = 256;
    octreeColorQuantizer.setPaletteSize(paletteSize);

    // Display quantization result
    cv::Mat originalVsQuantized = cv::Mat::zeros(demoPaletteImg.rows, demoPaletteImg.cols * 2 + 1, demoPaletteImg.type());
    demoPaletteImg.copyTo(originalVsQuantized(cv::Rect({0, 0}, demoPaletteImg.size())));
    octreeColorQuantizer.getQuantizedImage(demoPaletteImg).copyTo(originalVsQuantized(cv::Rect({demoPaletteImg.cols + 1, 0}, demoPaletteImg.size())));

    cv::imshow("Original (left) vs Quantized with " + std::to_string(paletteSize) + " colors (right)", originalVsQuantized);
    cv::waitKey();

    return 0;
}
