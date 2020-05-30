#ifndef OCTREECOLORQUANTIZER_HPP
#define OCTREECOLORQUANTIZER_HPP

#include "octreeNode.hpp"

class OctreeColorQuantizer
{
public:
    OctreeColorQuantizer(const cv::Mat& src);

    void setPaletteSize(const unsigned int paletteSize);
    cv::Mat getQuantizedImage(const cv::Mat& src) const;
    void resetPalette() const;

private:
    OctreeNode m_root;
    std::vector<OctreeNode*> m_sortedNodePtrs;
};

#endif // OCTREECOLORQUANTIZER_HPP
