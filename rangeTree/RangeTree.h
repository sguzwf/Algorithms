#include<iostream>
#include<stdio.h>
#include<vector>
#include<utility>
#include<algorithm>
#include<cassert>
#include<functional>
#include<string.h>

#include"def.h"
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::function;
struct Point
{
    double x, y, z;
    Point(double xx, double yy, double zz)
        : x(xx), y(yy), z(zz)
    {}
    void printPoint() const
    {
        printf("(%f,%f,%f)\n", x, y, z);
    }
    Point()
    {}
};
inline bool compX(const Point& p1, const Point& p2)
{
    return p1.x < p2.x;
}
inline bool compY(const Point& p1, const Point& p2)
{
    return p1.y < p2.y;
}
inline bool compZ(const Point& p1, const Point& p2)
{
    return p1.z < p2.z;
}
class RangeTree
{
private:
    double _key;
    int _dim;
    int _pointNum;

    bool _isLeaf;
    bool _isEmpty;
    RangeTree* _left;
    RangeTree* _right;
    RangeTree* _aux;
    Point* _data_1d;
    RangeTree* findSplitNode(double, double);
    void rangeQuery1D(double, double, vector<Point>&);
    // vector<Point> pointSort(size_t, const vector<Point>&) const;
public:
    double key() const
    {
        return _key;
    }
    RangeTree(Point*, unsigned short, int, bool );
    void RangeQuery(double[3][2], vector<Point>&);
    void exportPoints();
    ~RangeTree();
};
RangeTree::RangeTree(Point* points, unsigned short dim, int len, bool lastDimSorted)
    : _dim(dim), _pointNum(len)
{
    // is empty: points.empty()
    // is lear: only one distinct value in dim

    // pre sort
    // std::cout<<"here"<<std::endl;
    // _dim = dim;
    if (!lastDimSorted)
    {
        switch (dim)
        {
        case 3:
            std::sort(points, points + len, compZ);
            break;
        case 2:
            std::sort(points, points + len, compY);
            break;
        case 1:
            std::sort(points, points + len, compX);
            break;
        default:
            std::cout << "dim" << dim << std::endl;
            assert(0);
        }
    }
    // function<bool(const Point&,const Point&)> comp = [=](const Point& p1,const Point& p2)->bool{
    //     return p1[dim-1] < p2[dim-1];
    // };
    // std::sort(points.begin(), points.end(), comp);
    if (len == 0)
    {
        _key        = 0;
        _isLeaf     = true;
        _isEmpty    = true;
        _left       = nullptr;
        _right      = nullptr;
        _aux        = nullptr;
        return;
    }
    else if (dim == 1)
    {
        _data_1d = new Point[len];
        memcpy(_data_1d, points, len * sizeof(Point));
        _key     = _data_1d[len / 2].x;
        _isLeaf  = true;
        _isEmpty = false;
        _left    = nullptr;
        _right   = nullptr;
        _aux     = nullptr;
        return;
    }
    else
    {
        // for (auto p : points)
        //     _key += p[dim - 1];
        // _key /= points.size();
        decltype(len) middleIdx = (len - 1) / 2;
        auto p       = points[middleIdx];
        auto pLast   = points[len - 1];
        double lastV = (dim == 3 ? pLast.z : pLast.y);
        _key = (dim == 3 ? p.z : p.y);

        if (_key == lastV) // all kth coordinate equals
        {
            _isLeaf  = true;
            _isEmpty = false;
            _left    = nullptr;
            _right   = nullptr;
            _aux     = new RangeTree(points, dim - 1, len, false);
            return;
        }
        int leftLen        = middleIdx + 1;
        int rightLen       = len - leftLen;
        Point* leftPoints  = new Point[leftLen];
        Point* rightPoints = new Point[rightLen];
        memcpy(leftPoints, points, leftLen * sizeof(Point));
        memcpy(rightPoints, points + leftLen, rightLen * sizeof(Point));
        _isLeaf  = false;
        _isEmpty = false;
        _left    = new RangeTree(leftPoints, dim, leftLen, true);
        _right   = new RangeTree(rightPoints, dim, rightLen, true);
        _aux     = new RangeTree(points, dim - 1, len, false);
    }
}
RangeTree* RangeTree::findSplitNode(double left , double right)
{
    // if this is a bottol neck,
    // try refactoring this function into using iteration instead of recursion
    if (left <= _key && _key <= right)
    {
        return this;
    }
    else if (left > _key && _right)
    {
        return _right->findSplitNode(left, right);
    }
    else if (right < _key && _left)
    {
        return _left->findSplitNode(left, right);
    }
    else
    {
        return nullptr;
    }
}

void RangeTree::rangeQuery1D(double left, double right, vector<Point>& result)
{
    assert(_dim == 1);
    assert(_isLeaf);
    decltype(_pointNum) leftIdx  = 0;
    decltype(_pointNum) rightIdx = (_pointNum - 1);
    while (leftIdx < rightIdx)
    {
        decltype(leftIdx) middleIdx = (leftIdx + rightIdx) / 2;
        if (_data_1d[middleIdx].x > left)
            rightIdx = middleIdx;
        else if (_data_1d[middleIdx].x < left)
            leftIdx = middleIdx + 1;
    }
    decltype(leftIdx) startIdx = leftIdx;
    while (leftIdx < rightIdx)
    {
        decltype(leftIdx) middleIdx = (leftIdx + rightIdx) / 2;
        if (_data_1d[middleIdx].x > right)
            rightIdx = middleIdx;
        else if (_data_1d[middleIdx].x < right)
            leftIdx = middleIdx + 1;
    }
    decltype(rightIdx) endIdx = rightIdx;
    result.insert(result.end(), _data_1d + startIdx, _data_1d + endIdx);
    // while (_data_1d[leftIdx].x <= right && leftIdx < _pointNum)
    // {
    //     result.push_back(_data_1d[leftIdx]);
    //     leftIdx++;
    // }
}
void RangeTree::RangeQuery(double range[3][2], vector<Point>& result)
{
    // left and right edges of interval
    double left  = range[_dim - 1][0];
    double right = range[_dim - 1][1];

    auto s = findSplitNode(left, right);
    if ((!s) || s->_isEmpty) return;
    if (s->_isLeaf)
    {
        if (_dim == 1)
        {
            s->rangeQuery1D(left, right, result);
        }
        else
        {
            s->_aux->RangeQuery(range, result);
        }
        // assert(_dim == 1);
        // // s->rangeQuery1D(left, right, result);
        return;
    }
    auto v = s->_left;
    while (! v->_isLeaf)
    {
        if (left <= v->_key)
        {
            v->_aux->RangeQuery(range, result);
            v = v->_left;
        }
        else
        {
            v = v->_right;
        }
    }
    if (v->_key <= right && v->_key >= left)
        v->_aux->RangeQuery(range, result);
    //v->rangeQuery1D(range[0][0], range[0][1], result);
    v = s->_right;
    while (! v->_isLeaf)
    {
        if (right > v->_key)
        {
            v->_aux->RangeQuery(range, result);
            v = v->_right;
        }
        else
        {
            v = v->_left;
        }
    }
    if (v->_key <= right && v->_key >= left)
        v->_aux->RangeQuery(range, result);
    //v->rangeQuery1D(range[0][0], range[0][1], result);
}
void RangeTree::exportPoints()
{
    if (_isEmpty) return;
    if (_dim == 1)
    {
        for (decltype(_pointNum) i = 0; i < _pointNum; i++)
            _data_1d[i].printPoint();
    }
    else
    {
        if (_left) _left->exportPoints();
        if (_right) _right->exportPoints();
        if (_aux) _aux->exportPoints();
    }
}
RangeTree::~RangeTree()
{
    if (_left)    delete _left;
    if (_right)   delete _right;
    if (_aux)     delete _aux;
}

