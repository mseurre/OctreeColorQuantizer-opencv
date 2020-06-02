#include "octree.hpp"
#include "utils.hpp"

namespace impl
{

void Octree::insertColor(const cv::Vec3b& color)
{
    insertColor(utils::getMortonCodeFromColor(color), m_root);
}

cv::Vec3b Octree::getQuantizedColor(const cv::Vec3b& color) const
{
    return getQuantizedColor(utils::getMortonCodeFromColor(color), m_root);
}

void Octree::makePalette(const unsigned long paletteSize)
{
    if (!m_nodesSorted)
    {
        for (uchar i = 0; i < MAX_DEPTH; i++)
            std::sort(m_nodePtrsArray[i].begin(), m_nodePtrsArray[i].end(), [](const OctreeNode * nPtr1, const OctreeNode * nPtr2)
        {
            return nPtr1->m_colorCount < nPtr2->m_colorCount;
        });
        m_nodesSorted = true;
    }

    resetPalette();
    unsigned long totalLeafs = m_nodePtrsArray[MAX_DEPTH - 1].size();

    for (uchar depth = MAX_DEPTH - 2; depth > 0; depth--)
    {
        for (unsigned long nodeIdx = 0; nodeIdx < m_nodePtrsArray[depth].size(); nodeIdx++)
        {
            if (totalLeafs <= paletteSize)
                return;

            m_nodePtrsArray[depth][nodeIdx]->m_leaf = true;
            totalLeafs -= (m_nodePtrsArray[depth][nodeIdx]->m_activeChildCount - 1);
        }
    }
}

void Octree::resetPalette()
{
    for (uchar i = 0; i < MAX_DEPTH; i++)
        for (OctreeNode* nPtr : m_nodePtrsArray[i])
            nPtr->m_leaf = (i == MAX_DEPTH - 1);
}

std::vector<cv::Vec3b> Octree::getPaletteColors() const
{
    std::vector<cv::Vec3b> paletteColors;
    m_root.getLeafsColor(paletteColors);
    return paletteColors;
}

void Octree::insertColor(const unsigned int mortonCode, OctreeNode& node, const uchar currentDepth)
{
    if (currentDepth == MAX_DEPTH)
    {
        node.addColor(utils::getColorFromMortonCode(mortonCode));
    }
    else
    {
        const uchar childIdx = (mortonCode >> (3 * (MAX_DEPTH - 1 - currentDepth))) & 0b111;

        if (node.m_childPtrs[childIdx] == nullptr)
        {
            node.addChild(childIdx);
            m_nodePtrsArray[currentDepth].push_back(node.m_childPtrs[childIdx]);
        }

        insertColor(mortonCode, *node.m_childPtrs[childIdx], currentDepth + 1);
        node.addColor(utils::getColorFromMortonCode(mortonCode));
    }
}

cv::Vec3b Octree::getQuantizedColor(const unsigned int mortonCode, const OctreeNode& node, const uchar currentDepth) const
{
    if (currentDepth == MAX_DEPTH || node.m_leaf)
    {
        return node.getAverageColor();
    }
    else
    {
        const uchar childIdx = (mortonCode >> (3 * (MAX_DEPTH - 1 - currentDepth))) & 0b111;

        if (node.m_childPtrs[childIdx] == nullptr)
            return node.getAverageColor();
        else
            return getQuantizedColor(mortonCode, *node.m_childPtrs[childIdx], currentDepth + 1);
    }
}

}
