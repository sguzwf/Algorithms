#include<iostream>
#include<vector>
#include"Point.h"
using std::cout;
using std::endl;
using std::vector;
// 需要了解继承机制
// 三种不同的继承
// 了解public/private/protected
class VPTree
{
public:
    VPTree(vector<Point>&);
    ~VPTree();
    void search(const Point&, double, vector<Point>&) const;
    bool isLeaf() const;
    void exportPoints() const;
private:
    Point*  _p;
    double  _splitDistance;
    bool    _isLeaf;
    size_t  _pointsNum;
    VPTree* _left;
    VPTree* _right;
};
