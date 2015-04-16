#include"segment_tree.h"
#include<iostream>
#include<cassert>
#include<utility>
using std::pair;
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
    assert(s<t);
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
