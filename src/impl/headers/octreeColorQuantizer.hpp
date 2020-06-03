#ifndef OCTREECOLORQUANTIZER_HPP
#define OCTREECOLORQUANTIZER_HPP

#include "octree.hpp"
#include <opencv2/core/utility.hpp>


/**
 * @brief The OctreeColorQuantizer class is the interface between the image and the color quantization
 */
class OctreeColorQuantizer
{
public:
    /**
     * @brief Generate the octree based on a source image
     * @param src : the source image
     */
    OctreeColorQuantizer(const cv::Mat& src);

    /**
     * @brief Set the size of the desired quantized palette
     * @param paletteSize : the size of the palette
     */
    void setPaletteSize(const unsigned long paletteSize);

    /**
     * @brief Use all colors as a palette (no quantization)
     */
    void resetPalette();

    /**
     * @brief Compute the quantized equivalent of a source image (can be different from the image used for generating the octree)
     * @param src : the image to quantize
     * @return the quantized image
     */
    cv::Mat getQuantizedImage(const cv::Mat& src) const;

    /**
     * @brief Compute an image of the palette of colors used for quantization
     * @return the image of the color palette
     */
    cv::Mat getPaletteImage() const;

    unsigned long getPaletteSize() const;

private:
    impl::Octree m_octree;
};

#endif // OCTREECOLORQUANTIZER_HPP
