#include<iostream>
#include<vector>
#include<cassert>
#include<random>
#include"SegmentTree.h"
#include"Particle.h"
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
    _leafValues = nullptr;
}
StaticSegmentTree::StaticSegmentTree(double left, double right, double minInterval)
    : _leftRange(left), _rightRange(right)
{
    assert(left <= right);
    assert(minInterval > 0);
    if (right - left > minInterval)
    {
        // still need to split
        double middle = (right + left) / 2;
        _isLeaf       = false;
        _leftTree     = new StaticSegmentTree(left, middle, minInterval);
        _rightTree    = new StaticSegmentTree(middle , right, minInterval);
        _leafValues   = nullptr;
    }
    else
    {
        // leaf node
        _isLeaf     = true;
        _leftTree   = nullptr;
        _rightTree  = nullptr;
        _leafValues = new vector<Particle* >();
    }
}
void StaticSegmentTree::insert(Particle* p)
{
    double value = p->y();
    assert( _leftRange <= value && value <= _rightRange);
    if (_isLeaf)
    {
        // assert(_leafValues);
        // here the _leafValues should be guaranteed to be not empty
        // should I add one assert here?
        _leafValues->push_back(p);
        // assert(value == _leafValues->at(0));
    }
    else
    {
        double middle = (_leftRange + _rightRange) / 2;
        auto toInsert = value <= middle ? _leftTree : _rightTree;
        toInsert->insert(p);
    }
}
// vector<double> query(double, double);
vector<Particle* > StaticSegmentTree::query(double left, double right) const
{
    assert(left <= right);
    assert(left >= _leftRange);
    assert(right <= _rightRange);

    auto queryResult = vector<Particle* >();
    double middle = (_leftRange + _rightRange) / 2;
    if (_isLeaf)
    {
        // assert(left <= middle && middle <= right);
        for (auto p : *_leafValues)
        {
            double v = p->y();
            if (left <= v && v <= right)
                queryResult.push_back(p);
        }
    }
    else if (right <= middle)   // query range in the left subTree
    {
        queryResult = _leftTree->query(left, right);
    }
    else if (left > middle) // query range in the right subTree
    {
        queryResult = _rightTree->query(left, right);
    }
    else                        // query range in both left and right subTree
    {
        queryResult           = _leftTree->query(left, middle);
        auto rightQueryResult = _rightTree->query(middle, right);
        queryResult.insert(queryResult.end(), rightQueryResult.begin(), rightQueryResult.end());
    }
    return queryResult;
}

void autoSegmentTreeTest(const StaticSegmentTree& tree, unsigned int testNum, int leftRange, int rightRange)
{
    // 根据随机生成的range进行query, 再检测query的结果是否全部在range之中
    std::default_random_engine engine(std::random_device {}());
    std::uniform_real_distribution<double> distr(leftRange, rightRange);
    for (auto i = 0u; i < testNum; i++)
    {
        double rand1 = distr(engine);
        double rand2 = distr(engine);
        double left  = rand1 < rand2 ? rand1 : rand2;
        double right = rand1 < rand2 ? rand2 : rand1;
        auto queryResult = tree.query(left, right);
        for (Particle * p : queryResult)
        {
            double y = p->y();
            if (y > right || y < left)
            {
                std::cout << "Test failed" << std::endl;
                std::cout << "queryRange: (" << left << "," << right << ")" << std::endl;
                std::cout << "unusual particle queried:" << std::endl;
                p->printInfo();
                std::cout << "___________________________________________" << std::endl;
                return;
            }
        }
    }
    std::cout << "Test Successfully!" << std::endl;
    std::cout << "number of test case:" << testNum << std::endl;
    std::cout << "___________________________________________" << std::endl;
}
