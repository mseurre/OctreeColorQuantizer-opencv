#include "octreeNode.hpp"
#include "utils.hpp"
#define MAX_DEPTH 8

OctreeNode::OctreeNode()
{
    m_inPalette = true;
    m_colorCount = 0;
    m_colorSum = {0, 0, 0};

    for (uchar i = 0; i < 8; i++)
        m_childs[i] = nullptr;
}

OctreeNode::~OctreeNode()
{
    for (uchar i = 0; i < 8; i++)
        delete(m_childs[i]);
}

void OctreeNode::insertColor(const cv::Vec3b& color)
{
    insertColor(color, utils::getColorMortonCode(color));
}

cv::Vec3b OctreeNode::getQuantizedColor(const cv::Vec3b& color) const
{
    return getQuantizedColor(utils::getColorMortonCode(color));
}

std::vector<OctreeNode*> OctreeNode::getActiveChildsPtrs() const
{
    std::vector<OctreeNode*> activeChildPtrs;

    for (uchar i = 0; i < 8; i++)
    {
        if (m_childs[i] != nullptr)
        {
            activeChildPtrs.push_back(m_childs[i]);
            std::vector<OctreeNode*> nextChildPtrs = m_childs[i]->getActiveChildsPtrs();
            activeChildPtrs.insert(activeChildPtrs.end(), nextChildPtrs.begin(), nextChildPtrs.end());
        }
    }

    return activeChildPtrs;
}

cv::Vec3b OctreeNode::getAverageColor() const
{
    return { static_cast<uchar>(m_colorSum[0] / m_colorCount),
             static_cast<uchar>(m_colorSum[1] / m_colorCount),
             static_cast<uchar>(m_colorSum[2] / m_colorCount) };
}

unsigned int OctreeNode::getCount() const
{
    return m_colorCount;
}

void OctreeNode::setInPalette(const bool inPalette)
{
    m_inPalette = inPalette;
}

void OctreeNode::insertColor(const cv::Vec3b& color, const unsigned int mortonCode, const uchar currentDepth)
{
    if (currentDepth == MAX_DEPTH)
    {
        m_colorSum += color;
        m_colorCount++;
    }
    else
    {
        const uchar childIdx = (mortonCode & 0b111);

        if (m_childs[childIdx] == nullptr)
            m_childs[childIdx] = new OctreeNode();

        m_childs[childIdx]->insertColor(color, mortonCode >> 3, currentDepth + 1);
        m_colorSum += color;
        m_colorCount++;
    }
}

cv::Vec3b OctreeNode::getQuantizedColor(const unsigned int mortonCode, const uchar currentDepth) const
{
    if (currentDepth == MAX_DEPTH)
    {
        return getAverageColor();
    }
    else
    {
        const uchar childIdx = (mortonCode & 0b111);

        if (m_childs[childIdx] == nullptr || !m_childs[childIdx]->m_inPalette)
            return getAverageColor();

        else
            return m_childs[childIdx]->getQuantizedColor(mortonCode >> 3, currentDepth + 1);
    }
}
