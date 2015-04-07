#include<iostream>
#include<vector>
#include<cassert>
#include<random>
#include"segmentTree.h"
using std::vector;
StaticSegmentTree::~StaticSegmentTree()
{
    if (_leftTree)
    {
        delete _leftTree;
    }
    if (_rightTree)
    {
        delete _rightTree;
    }
    delete _leafValues;
}
StaticSegmentTree::StaticSegmentTree(long left, long right)
    : _leftRange(left), _rightRange(right)
{
    assert(left <= right);
    if (right - left >= 1)
    {
        // still need to split
        long middle = (right + left) / 2;
        _isLeaf     = false;
        _leftTree   = new StaticSegmentTree(left, middle);
        _rightTree  = new StaticSegmentTree(middle + 1, right);
        _leafValues = nullptr;
    }
    else
    {
        // leaf node
        _isLeaf     = true;
        _leftTree   = nullptr;
        _rightTree  = nullptr;
        _leafValues = new vector<long>();
    }
}
void StaticSegmentTree::insert(long value)
{
    assert( _leftRange <= value && value <= _rightRange);
    if (_isLeaf)
    {
        // assert(_leafValues);
        // here the _leafValues should be guaranteed to be not empty
        // should I add one assert here?
        _leafValues->push_back(value);
        // assert(value == _leafValues->at(0));
    }
    else
    {
        long middle = (_leftRange + _rightRange) / 2;
        auto toInsert = value <= middle ? _leftTree : _rightTree;
        toInsert->insert(value);
    }
}
// vector<long> query(long, long);
vector<long> StaticSegmentTree::query(long left, long right) const
{
    assert(left <= right);
    assert(left >= _leftRange);
    assert(right <= _rightRange);

    auto queryResult = vector<long>();
    long middle = (_leftRange + _rightRange) / 2;
    if (_isLeaf)
    {
        assert(left <= middle && middle <= right);
        queryResult = *_leafValues;
        // queryResult.insert(queryResult.end(),_leafValues->begin(),_leafValues->end());
    }
    else if (right <= middle)   // query range in the left subTree
    {
        queryResult = _leftTree->query(left, right);
    }
    else if (left >= middle + 1) // query range in the right subTree
    {
        queryResult = _rightTree->query(left, right);
    }
    else                        // query range in both left and right subTree
    {
        queryResult           = _leftTree->query(left, middle);
        auto rightQueryResult = _rightTree->query(middle + 1, right);
        queryResult.insert(queryResult.end(), rightQueryResult.begin(), rightQueryResult.end());
    }
    return queryResult;
}
