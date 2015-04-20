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
    Point()
    {}
};
void printPoints(Point* pArr, int len)
{
    for (int i = 0; i < len; i++)
        cout << "(" << pArr[i].x << "," << pArr[i].y << "," << pArr[i].z << ")" << endl;
}
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

    bool _isLeaf;
    bool _isEmpty;
    RangeTree* _left;
    RangeTree* _right;
    RangeTree* _aux;
    Point* _data_1d;

    // vector<Point> pointSort(size_t, const vector<Point>&) const;
public:
    double key() const
    {
        return _key;
    }
    RangeTree(Point*, unsigned short, int, bool );
    ~RangeTree();
};
RangeTree::RangeTree(Point* points, unsigned short dim, int len, bool lastDimSorted)
{
    // is empty: points.empty()
    // is lear: only one distinct value in dim

    // pre sort
    // std::cout<<"here"<<std::endl;
    _dim = dim;
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
        auto p       = points[len / 2];
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
        int leftLen        = len / 2 + 1;
        int rightLen       = len - (len / 2 + 1);
        Point* leftPoints  = new Point[leftLen];
        Point* rightPoints = new Point[rightLen];
        memcpy(leftPoints, points, leftLen * sizeof(Point));
        memcpy(rightPoints, points + len / 2 + 1, rightLen * sizeof(Point));
        _isLeaf  = false;
        _isEmpty = false;
        // printPoints(leftPoints,leftLen);
        _left    = new RangeTree(leftPoints, dim, leftLen, true);
        _right   = new RangeTree(rightPoints, dim, rightLen, true);
        _aux     = new RangeTree(points, dim - 1, len, false);
    }
}
RangeTree::~RangeTree()
{
    if (_left)    delete _left;
    if (_right)   delete _right;
    if (_aux)     delete _aux;
}

