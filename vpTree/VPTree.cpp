#include<vector>
#include<iostream>
#include<cassert>
#include<limits>
#include<algorithm>
#include"VPTree.h"
using std::cout;
using std::endl;
using std::vector;
VPTree::VPTree(vector<Point>& points)
    : _pointsNum(points.size())
{
    if (_pointsNum == 0)
    {
        // empty point set, return empty tree
        _p      = nullptr;
        _left   = nullptr;
        _right  = nullptr;
        _isLeaf = true;
        _splitDistance = std::numeric_limits<double>::infinity();
    }
    else if (_pointsNum == 1)
    {
        // only one point, we get a leaf node
        _p      = new Point(points[0]);
        _left   = nullptr;
        _right  = nullptr;
        _isLeaf = true;
        _splitDistance = std::numeric_limits<double>::infinity();
    }
    else
    {
        // an internal node
        _p = new Point(points[0]);
        // the first point(vantage point, would not be in left)
        // so firstIdx is 1 instead of 0
        decltype(points.size()) firstIdx = 1;
        decltype(points.size()) lastIdx  = points.size() - 1;
        decltype(points.size()) middIdx  = (firstIdx + lastIdx) / 2;
        auto firstIter = points.begin() + firstIdx;
        auto middIter  = points.begin() + middIdx;
        // the nth element would be median, 
        // and element before median would have a distance smaller than median distance
        std::nth_element( firstIter, middIter, points.end(), [&](const Point & p1, const Point & p2)->bool
        {
            return _p->distance(p1) < _p->distance(p2);
        });
        _splitDistance = _p->distance(points[middIdx]);
        decltype(middIdx) leftLen   = middIdx - firstIdx + 1;
        decltype(middIdx) rightLen  = lastIdx - middIdx;
        vector<Point> left, right;
        std::copy_n(firstIter,    leftLen,  std::back_inserter(left));
        std::copy_n(middIter + 1, rightLen, std::back_inserter(right));
        _left  = left.empty()  ? nullptr : new VPTree(left);
        _right = right.empty() ? nullptr : new VPTree(right);
    }
}
VPTree::~VPTree()
{
    delete _p;
    delete _left;
    delete _right;
}
bool VPTree::isLeaf() const
{
    return _isLeaf;
}
void VPTree::exportPoints() const
{
    assert(_p != nullptr);
    _p->printPoint();
    if (_left)
        _left->exportPoints();
    if (_right)
        _right->exportPoints();
}
