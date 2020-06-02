#ifndef OCTREE_HPP
#define OCTREE_HPP

#define MAX_DEPTH 8

#include "octreeNode.hpp"

namespace impl
{

/**
 * @brief The Octree class implements multiple mechanisms : inserting a new color, creating the palette, getting the quantized color, getting the palette image
 */
class Octree
{
public:
    /**
     * @brief Insert a color into the tree
     * @param color : the color to insert
     */
    void insertColor(const cv::Vec3b& color);

    /**
     * @brief Get the quantized color corresponding to the arg color
     * @param color : the color which's quantized equivalent to get
     * @return the quantized color
     */
    cv::Vec3b getQuantizedColor(const cv::Vec3b& color) const;

    /**
     * @brief Create a palette of "paletteSize" quantized color
     * @param paletteSize : the size of the palette
     */
    void makePalette(const unsigned long paletteSize);

    /**
     * @brief Use all octree leafs as a palette (no quantization)
     */
    void resetPalette();

    /**
     * @brief Get all colors used in the current palette
     * @return the vector of palette colors
     */
    std::vector<cv::Vec3b> getPaletteColors() const;

private:
    OctreeNode m_root;
    std::array<std::vector<OctreeNode*>, MAX_DEPTH> m_nodePtrsArray;
    bool m_nodesSorted;

    /**
     * @brief Implementation of the color insertion algorithm (recursive)
     * @param mortonCode : the morton code of the color to insert
     * @param currentDepth : the current depth of insertion of the color
     */
    void insertColor(const unsigned int mortonCode, OctreeNode& node, const uchar currentDepth = 0);

    /**
     * @brief Implementation of the color fetch algorithm (recursive)
     * @param mortonCode : the morton code of the color to fetch
     * @param currentDepth : the current depth of fetch
     * @return the quantized color found at the location given by the morton code
     */
    cv::Vec3b getQuantizedColor(const unsigned int mortonCode, const OctreeNode& node, const uchar currentDepth = 0) const;
};

}

#endif // OCTREE_HPP
