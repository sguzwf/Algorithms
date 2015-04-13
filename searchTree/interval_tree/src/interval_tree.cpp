#include"interval_tree.h"
#include"qsort.h"
#include<vector>
#include<cassert>
using std::vector;
Interval::Interval(double l, double r)
    : _left(l), _right(r)
{}
double Interval::left() const
{
    return _left;
}
double Interval::right() const
{
    return _right;
}

double IntervalTree::middlePoint(const vector<Interval>& intervals)
{
    size_t size  = intervals.size();
    double sum = 0;
    for (auto v : intervals)
    {
        sum += v.left();
        sum += v.right();
    }
    double mid = sum / (size * 2);
    return mid;
}
void IntervalTree::partition(
    const vector<Interval>& interv,
    vector<Interval>& left,
    vector<Interval>& right,
    vector<Interval>& middle,
    double midPoint)
{
    for (auto v : interv)
    {
        if (v.right() < midPoint)
        {
            left.push_back(v);
        }
        else if (v.left() > midPoint)
        {
            right.push_back(v);
        }
        else
        {
            middle.push_back(v);
        }
    }
}
const IntervalTree* IntervalTree::left() const
{
    assert(_empty == false);
    return _left;
}
const IntervalTree* IntervalTree::right() const
{
    assert(_empty == false);
    return _right;
}
double IntervalTree::key() const
{
    assert(_empty == false);
    return _key;
}
bool IntervalTree::empty() const
{
    return _empty;
}
IntervalTree::IntervalTree(const vector<Interval>& intervals)
{
    if (intervals.empty())
    {
        _empty = true;
        return;
    }
    double midPoint = middlePoint(intervals);
    vector<Interval> left;
    vector<Interval> right;
    vector<Interval> midd;
    partition(intervals, left, right, midd, midPoint);
    vector<double> leftEnds;
    vector<double> rightEnds;
    leftEnds.reserve(midd.size());
    rightEnds.reserve(midd.size());
    for(auto v : midd)
    {
        leftEnds.push_back(v.left());
        rightEnds.push_back(v.right());
    }
    function<bool(double,double)> less    = std::less<double>();
    function<bool(double,double)> greater = std::greater_equal<double>();
    _empty         = false;
    _key           = midPoint;
    _left          = new IntervalTree(left);
    _right         = new IntervalTree(right);
    _aux->leftEnd  = qsort(leftEnds,less);
    _aux->rightEnd = qsort(rightEnds,greater);
}
