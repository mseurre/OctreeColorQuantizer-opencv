#include "octreeColorQuantizer.hpp"
#include <opencv2/core/mat.hpp>

OctreeColorQuantizer::OctreeColorQuantizer(const cv::Mat& src)
{
    const uchar nbChannels = static_cast<uchar>(std::min(src.channels(), 3));

    for (int i = 0; i < src.rows * src.cols; i++)
    {
        cv::Vec3b color;

        for (uchar c = 0; c < nbChannels; c++)
            color[c] = src.ptr<uchar>(0)[i * src.channels() + c];

        m_octree.insertColor(color);
    }

    resetPalette();
}

void OctreeColorQuantizer::setPaletteSize(const unsigned long paletteSize)
{
    m_octree.makePalette(paletteSize);
}

void OctreeColorQuantizer::resetPalette()
{
    m_octree.resetPalette();
}

unsigned long OctreeColorQuantizer::getPaletteSize() const
{
    return m_octree.getPaletteSize();
}

cv::Mat OctreeColorQuantizer::getQuantizedImage(const cv::Mat& src) const
{
    cv::Mat quantizedImage(src.size(), src.type());
    const uchar nbChannels = static_cast<uchar>(std::min(src.channels(), 3));

    cv::parallel_for_(cv::Range(0, src.rows * src.cols), [&](const cv::Range & range)
    {
        for (int r = range.start; r < range.end; r++)
        {
            cv::Vec3b colorSrc, colorOut;

            for (uchar c = 0; c < nbChannels; c++)
                colorSrc[c] = src.ptr<uchar>(0)[r * src.channels() + c];

            colorOut = m_octree.getQuantizedColor(colorSrc);

            for (uchar c = 0; c < nbChannels; c++)
                quantizedImage.ptr<uchar>(0)[r * quantizedImage.channels() + c] = colorOut[c];
        }
    });

    return quantizedImage;
}

cv::Mat OctreeColorQuantizer::getPaletteImage() const
{
    const std::vector<cv::Vec3b> paletteColors = m_octree.getPaletteColors();

    unsigned long paletteImageSize = static_cast<unsigned long>(std::ceil(std::sqrt(paletteColors.size())));

    cv::Mat paletteImage = cv::Mat::zeros(paletteImageSize, paletteImageSize, CV_8UC3);
    uchar* paletteDataPtr = paletteImage.ptr<uchar>(0);

    for (unsigned long i = 0; i < paletteColors.size(); i++)
    {
        for (uchar c = 0; c < paletteImage.channels(); c++)
            paletteDataPtr[i * paletteImage.channels() + c] = paletteColors[i][c];
    }

    return paletteImage;
}
