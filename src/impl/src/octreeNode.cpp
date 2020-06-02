#include "octreeNode.hpp"

namespace impl
{

OctreeNode::OctreeNode()
{
    for (uchar i = 0; i < 8; i++)
        m_childPtrs[i] = nullptr;

    m_colorCount = 0;
    m_colorSum = {0, 0, 0};
    m_activeChildCount = 0;
    m_leaf = false;
}

OctreeNode::~OctreeNode()
{
    for (uchar i = 0; i < 8; i++)
        delete(m_childPtrs[i]);
}

void OctreeNode::addChild(const uchar childIdx)
{
    m_childPtrs[childIdx] = new OctreeNode();
    m_activeChildCount++;
}

void OctreeNode::addColor(const cv::Vec3b& color)
{
    m_colorSum += color;
    m_colorCount++;
}

cv::Vec3b OctreeNode::getAverageColor() const
{
    return { static_cast<uchar>(m_colorSum[0] / m_colorCount),
             static_cast<uchar>(m_colorSum[1] / m_colorCount),
             static_cast<uchar>(m_colorSum[2] / m_colorCount) };
}

void OctreeNode::getLeafsColor(std::vector<cv::Vec3b>& colors) const
{
    if (m_leaf)
        colors.push_back({ getAverageColor() });

    else
        for (uchar i = 0; i < 8; i++)
            if (m_childPtrs[i] != nullptr)
                m_childPtrs[i]->getLeafsColor(colors);
}

}
