#include "impl/headers/octreeColorQuantizer.hpp"
#include <opencv2/highgui.hpp>
#include "impl/headers/utils.hpp"

int main(int /*argc*/, char** /*argv*/)
{
    // Input image
    const cv::Mat demoPaletteImg = utils::getDemoPaletteImage(600);

    // Generate the octree quantizer
    OctreeColorQuantizer octreeColorQuantizer(demoPaletteImg);

    // Make a quantization palette with only 256 values
    const unsigned int paletteSize = 256;
    octreeColorQuantizer.setPaletteSize(paletteSize);

    // Display quantization result
    cv::Mat originalVsQuantized = cv::Mat::zeros(demoPaletteImg.rows, demoPaletteImg.cols * 2 + 1, demoPaletteImg.type());
    demoPaletteImg.copyTo(originalVsQuantized(cv::Rect({0, 0}, demoPaletteImg.size())));
    octreeColorQuantizer.getQuantizedImage(demoPaletteImg).copyTo(originalVsQuantized(cv::Rect({demoPaletteImg.cols + 1, 0}, demoPaletteImg.size())));

    cv::imshow("Original vs Quantized to " + std::to_string(paletteSize) + " colors", originalVsQuantized);
    cv::waitKey();

    return 0;
}
