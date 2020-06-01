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
            color[c] = pSrcData[i * src.channels() + c];

        m_root.insertColor(color);
    }

    m_sortedNodePtrs = m_root.getActiveChildsPtrs();
    std::sort(m_sortedNodePtrs.begin(), m_sortedNodePtrs.end(), [](const OctreeNode * n1, const OctreeNode * n2)
    {
        return n1->getCount() < n2->getCount() ;
    });
}

void OctreeColorQuantizer::setPaletteSize(const unsigned int paletteSize)
{
    for (unsigned int i = 0; i < m_sortedNodePtrs.size(); i++)
        m_sortedNodePtrs[i]->setInPalette(i > m_sortedNodePtrs.size() - paletteSize);
}

void OctreeColorQuantizer::resetPalette() const
{
    for (OctreeNode* nPtr : m_sortedNodePtrs)
        nPtr->setInPalette(true);
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
            colorSrc[c] = pSrcData[i * src.channels() + c];

        colorOut = m_root.getQuantizedColor(colorSrc);

        for (uchar c = 0; c < nbChannels; c++)
            pQuantizedData[i * quantizedImage.channels() + c] = colorOut[c];
    }

    return quantizedImage;
}
