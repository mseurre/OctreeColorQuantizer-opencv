#ifndef OCTREECOLORQUANTIZER_HPP
#define OCTREECOLORQUANTIZER_HPP

#include "octreeNode.hpp"

/**
 * @brief The OctreeColorQuantizer class which implements the interface between the image and the color quantization
 */
class OctreeColorQuantizer
{
public:

    /**
     * @brief In the constructor, the octree is generated based on a source image
     * @param src : the source image
     */
    OctreeColorQuantizer(const cv::Mat& src);

    /**
     * @brief Set the size of the desired quantized palette
     * @param paletteSize the size of the palette
     */
    void setPaletteSize(const unsigned int paletteSize);

    /**
     * @brief Use all octree colors as a palette (no quantization)
     */
    void resetPalette() const;

    /**
     * @brief Compute the quantized equivalent of a source image (can be different from the image used for generating the octree)
     * @param src : the image to quantize
     * @return the quantized image
     */
    cv::Mat getQuantizedImage(const cv::Mat& src) const;

private:
    OctreeNode m_root;
    std::vector<OctreeNode*> m_sortedNodePtrs;
};

#endif // OCTREECOLORQUANTIZER_HPP
