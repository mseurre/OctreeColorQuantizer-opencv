#ifndef OCTREENODE_HPP
#define OCTREENODE_HPP

#include <opencv2/core/matx.hpp>

namespace impl
{

/**
 * @brief The OctreeNode struct represents an element of an Octree.
 */
struct OctreeNode
{
    OctreeNode();
    ~OctreeNode();

    /**
     * @brief Add a child and update the active child count
     * @param childIdx : the index of the child to add
     */
    void addChild(const uchar childIdx);

    /**
     * @brief Add a color to a node and increment the color counter
     * @param color : the color to add
     */
    void addColor(const cv::Vec3b& color);

    /**
     * @brief Compute the average color of a node (colorSum / colorCount)
     * @return the average color
     */
    cv::Vec3b getAverageColor() const;

    /**
     * @brief Recursively fill a vector with each leaf's color
     * @param colors : the vector of leaf colors
     */
    void getLeafsColor(std::vector<cv::Vec3b>& colors) const;

    std::array<OctreeNode*, 8> m_childPtrs;
    unsigned long m_colorCount;
    cv::Vec3f m_colorSum;
    uchar m_activeChildCount;
    bool m_leaf;
};

}

#endif // OCTREENODE_HPP
