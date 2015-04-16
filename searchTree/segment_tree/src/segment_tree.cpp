#include"segment_tree.h"
#include<iostream>
#include<cassert>
#include<utility>
#include<cmath>
#include<vector>
using std::pair;
using std::vector;
using std::cout;
using std::endl;

SegmentTree::SegmentTree()
    : _isLeaf(true),
      _key(0),
      _left(nullptr),
      _right(nullptr),
      _range(pair<int, int>(0, 0))
{
}

SegmentTree::~SegmentTree()
{
    delete _left;
    delete _right;
}
SegmentTree::SegmentTree(int s, int t)
    : _range(pair<int, int>(s, t))
{
    assert(s < t);
    if (s + 1 == t)
    {
        _isLeaf = true;
        _left   = nullptr;
        _right  = nullptr;
        _key    = 0;
    }
    else
    {
        _isLeaf = false;
        _key    = (s + t) / 2;
        _left   = new SegmentTree(s, _key);
        _right  = new SegmentTree(_key, t);
    }
}
int SegmentTree::rangeLeft() const
{
    return _range.first;
}
int SegmentTree::rangeRight() const
{
    return _range.second;
}
vector<SegmentTree*> SegmentTree::Interval_Insertion(int left, int right)
{
    // input an interval [left,right]
    // return all the nodes whose standard range are in the canonical covering of [left,right]
    assert(right >= left);
    auto   retVec   = vector<SegmentTree*>();
    double afterLog = log2(right - left);
    retVec.reserve(round(afterLog) + floor(afterLog) - 2);

    if (_range.first >= left && _range.second <= right)
    {
        // in range
        retVec.push_back(this);
        return retVec;
    }
    if (left < _key)
    {
        auto tmpVec = _left->Interval_Insertion(left, right);
        retVec.insert(retVec.end(), tmpVec.begin(), tmpVec.end());
    }
    if (_key < right)
    {
        auto tmpVec = _right->Interval_Insertion(left, right);
        retVec.insert(retVec.end(), tmpVec.begin(), tmpVec.end());
    }
    return retVec;
}
