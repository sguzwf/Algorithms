#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H
#include<iostream>
#include<vector>
#include<cassert>
#include"Particle.h"
using std::vector;

class StaticSegmentTree
{
    // static segment tree
    // only Particle element
public:
    StaticSegmentTree(double left, double right, double minInterval);
    ~StaticSegmentTree();
    void insert(Particle*);
    vector<Particle*> query(double, double)const;
    double leftRange() const {return _leftRange;}
    double rightRange() const {return _rightRange;}
    StaticSegmentTree& operator=(const StaticSegmentTree&);
private:
    bool _isLeaf;
    StaticSegmentTree* _leftTree;
    StaticSegmentTree* _rightTree;
    double _leftRange;
    double _rightRange;
    
    // 之所以用指针，而不直接用vector
    // 是因为在非叶节点上是没有_leafValues的，
    // 用指针可以设为空指针
    // 如果用vector, 则及时是空vector，sizeof(vec)也是24
    // 不过我也不知道这样是不是合理。
    vector<Particle*>* _leafValues = nullptr;
};
bool autoSegmentTreeTest(const StaticSegmentTree& , unsigned int , int , int );
#endif
