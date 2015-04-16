#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H
#include"utility"
using std::pair;
class SegmentTree
{
public:
    SegmentTree();
    SegmentTree(int s, int t);
    ~SegmentTree();
    int rangeLeft();
    int rangeRight();
    SegmentTree* leftTree();
    SegmentTree* rightTree();
private:
    // 禁止拷贝，禁止赋值
    SegmentTree(const SegmentTree&);
    SegmentTree& operator=(const SegmentTree&);

    bool _isLeaf;
    int _key;
    SegmentTree* _left;
    SegmentTree* _right;
    pair<int,int> _range;
};
#endif
