#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H
#include<vector>
#include<cassert>
#include<iostream>
using std::vector;
class StaticSegmentTree
{
    // static segment tree
    // only integer element
public:
    StaticSegmentTree(long left, long right);
    ~StaticSegmentTree();
    void insert(long);
    vector<long> query(long, long)const;
    long leftRange() const {return _leftRange;}
    long rightRange() const {return _rightRange;}
private:
    bool _isLeaf;
    vector<long>* _leafValues = nullptr;
    StaticSegmentTree* _leftTree;
    StaticSegmentTree* _rightTree;
    long _leftRange;
    long _rightRange;
};
#endif
