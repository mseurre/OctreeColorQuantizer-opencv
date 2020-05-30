#ifndef OCTREENODE_HPP
#define OCTREENODE_HPP

#include <opencv2/core/matx.hpp>

class OctreeNode
{
public:
    OctreeNode();
    ~OctreeNode();

    void insertColor(const cv::Vec3b& color, const unsigned int mortonCode, const uchar currentDepth = 0);
    cv::Vec3b getColor(const unsigned int mortonCode, const uchar currentDepth = 0) const;

    std::vector<OctreeNode*> getActiveChildsPtrs() const;
    cv::Vec3b getAverageColor() const;
    unsigned int getCount() const;
    void setInPalette(const bool inPalette);

private:
    bool m_inPalette;
    unsigned int m_colorCount;
    cv::Vec3f m_colorSum;
    std::array<OctreeNode*, 8> m_childs;
};

#endif // OCTREENODE_HPP
