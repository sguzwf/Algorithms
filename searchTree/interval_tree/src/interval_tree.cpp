#include"interval_tree.h"
#include"qsort.h"
#include<vector>
#include<cassert>
using std::vector;
Interval::Interval(double l, double r)
    : _left(l), _right(r)
{
    assert(l <= r);
}
double Interval::left() const
{
    return _left;
}
double Interval::right() const
{
    return _right;
}
bool Interval::overlap(const Interval& interv) const
{
    if (interv._left > _right)
        return false;
    if (interv._right < _left)
        return false;
    return true;
}
bool Interval::inRange(double v) const
{
    return v <= _right && v >= _left;
}
double IntervalTree::middlePoint(const vector<Interval>& intervals)
{
    //private function
    size_t vSize = intervals.size();
    double sum   = 0;
    for (auto & v : intervals)
        sum += (v.left() + v.right());
    return sum / (vSize * 2);
}
void IntervalTree::partition(
    const vector<Interval>& interv,
    double midPoint,
    vector<Interval>& left,
    vector<Interval>& right,
    vector<Interval>& middle)
{
    for (auto & v : interv)
    {
        if (v.right() < midPoint)
            left.push_back(v);
        else if (v.left() > midPoint)
            right.push_back(v);
        else
            middle.push_back(v);
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
    partition(intervals, midPoint, left, right, midd);
    static const auto leftLess = [](const Interval & interv1, const Interval & interv2)->bool
    {
        return interv1.left() < interv2.left();
    };
    static const auto leftEq = [](const Interval & interv1, const Interval & interv2)->bool
    {
        return interv1.left() == interv2.left();
    };
    static const auto rightLess = [](const Interval & interv1, const Interval & interv2)->bool
    {
        return interv1.right() < interv2.right();
    };
    static const auto rightEq = [](const Interval & interv1, const Interval & interv2)->bool
    {
        return interv1.right() == interv2.right();
    };
    middleLeft  = qsort<Interval>(midd, leftLess, leftEq);
    middleRight = qsort<Interval>(midd, rightLess, rightEq);
    _empty      = false;
    _key        = midPoint;
    _left       = new IntervalTree(left);
    _right      = new IntervalTree(right);
}
vector<Interval> IntervalTree::intervalSearch(const Interval& queryInterv)
{
    vector<Interval> result;
    if (queryInterv.inRange(_key))
    {
        auto result_left  = _left->intervalSearch(queryInterv);
        auto result_right = _left->intervalSearch(queryInterv);
        result.insert(result.end(), middleLeft.begin(), middleLeft.end());
        result.insert(result.end(), result_left.begin(), result_left.end());
        result.insert(result.end(), result_right.begin(), result_right.end());
    }
    else if (queryInterv.right() < _key)
    {
        auto result_left  = _left->intervalSearch(queryInterv);
        for (auto & interv : middleLeft)
        {
            if (interv.left() <= queryInterv.right())
                result.push_back(interv);
            else
                break; // already sorted
        }
        result.insert(result.end(), result_left.begin(), result_left.end());
    }
    else if (queryInterv.left() > _key)
    {
        auto result_right = _right->intervalSearch(queryInterv);
        for (auto & interv : middleRight)
        {
            if (interv.right() >= queryInterv.left())
                result.push_back(interv);
            else
                break;
        }
        result.insert(result.end(), result_right.begin(), result_right.end());
    }
    else assert(0);
    return result;
}
