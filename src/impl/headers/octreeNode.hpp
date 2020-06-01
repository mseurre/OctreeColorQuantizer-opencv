#ifndef OCTREENODE_HPP
#define OCTREENODE_HPP

#include <opencv2/core/matx.hpp>

/**
 * @brief The OctreeNode class which implements the octree mechanisms
 */
class OctreeNode
{
public:
    OctreeNode();
    ~OctreeNode();

    /**
     * @brief Insert a color into a node
     * @param color : the color to insert
     */
    void insertColor(const cv::Vec3b& color);

    /**
     * @brief Get the quantized equivalent of a color
     * @param color : the color which quantized equivalent to return
     * @return the quantized color
     */
    cv::Vec3b getQuantizedColor(const cv::Vec3b& color) const;

    /**
     * @brief Get a vector of all active childs of a node (including the childs of the childs, etc)
     * @return a vector of OctreeNode pointers
     */
    std::vector<OctreeNode*> getActiveChildsPtrs() const;

    /**
     * @brief Compute the average color of a node (colorSum / colorCount)
     * @return the average color
     */
    cv::Vec3b getAverageColor() const;

    /**
     * @brief Get the color count of a node
     * @return the color count
     */
    unsigned int getCount() const;

    /**
     * @brief Set whether or not a node's color is part of the quantized palette
     * @param inPalette : True if it is, false otherwise
     */
    void setInPalette(const bool inPalette);

private:
    bool m_inPalette;
    unsigned int m_colorCount;
    cv::Vec3f m_colorSum;
    std::array<OctreeNode*, 8> m_childs;

    /**
     * @brief Implementation of the color insertion algorithm (recursive)
     * @param color : the color to insert
     * @param mortonCode : the morton code of the color to insert
     * @param currentDepth : the current depth of insertion of the color
     */
    void insertColor(const cv::Vec3b& color, const unsigned int mortonCode, const uchar currentDepth = 0);

    /**
     * @brief Implementation of the color fetch algorithm (recursive)
     * @param mortonCode : the morton code of the color to fetch
     * @param currentDepth : the current depth of fetch
     * @return the quantized color found the location given by the morton code
     */
    cv::Vec3b getQuantizedColor(const unsigned int mortonCode, const uchar currentDepth = 0) const;
};

#endif // OCTREENODE_HPP
