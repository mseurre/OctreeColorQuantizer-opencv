#include "octreeColorQuantizer.hpp"
#include <opencv2/core/mat.hpp>

OctreeColorQuantizer::OctreeColorQuantizer(const cv::Mat& src)
{
    const uchar* pSrcData = src.ptr<uchar>(0);
    const uchar nbChannels = static_cast<uchar>(std::min(src.channels(), 3));
    cv::Vec3b color;

    for (unsigned int i = 0; i < src.total(); i++)
    {
        for (uchar c = 0; c < nbChannels; c++)
            color[c] = pSrcData[i * static_cast<uchar>(src.channels()) + c];

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

cv::Mat OctreeColorQuantizer::getQuantizedImage(const cv::Mat& src) const
{
    cv::Mat quantizedImage(src.size(), src.type());

    const uchar* pSrcData = src.ptr<uchar>(0);
    uchar* pQuantizedData = quantizedImage.ptr<uchar>(0);
    const uchar nbChannels = static_cast<uchar>(std::min(src.channels(), 3));
    cv::Vec3b colorSrc, colorOut;

    for (unsigned int i = 0; i < src.total(); i++)
    {
        for (uchar c = 0; c < nbChannels; c++)
            colorSrc[c] = pSrcData[i * static_cast<uchar>(src.channels()) + c];

        colorOut = m_octree.getQuantizedColor(colorSrc);

        for (uchar c = 0; c < nbChannels; c++)
            pQuantizedData[i * static_cast<uchar>(quantizedImage.channels()) + c] = colorOut[c];
    }

    return quantizedImage;
}

cv::Mat OctreeColorQuantizer::getPaletteImage() const
{
    const std::vector<cv::Vec3b> paletteColors = m_octree.getPaletteColors();

    unsigned long paletteImageSize = paletteColors.size();

    while (std::sqrt(paletteImageSize) != std::floor(std::sqrt(paletteImageSize)))
        paletteImageSize++;

    paletteImageSize = static_cast<unsigned long>(std::sqrt(paletteImageSize));

    cv::Mat paletteImage = cv::Mat::zeros(paletteImageSize, paletteImageSize, CV_8UC3);
    uchar* paletteDataPtr = paletteImage.ptr<uchar>(0);

    for (unsigned long i = 0; i < paletteColors.size(); i++)
    {
        for (uchar c = 0; c < paletteImage.channels(); c++)
            paletteDataPtr[i * paletteImage.channels() + c] = paletteColors[i][c];
    }

    return paletteImage;
}
