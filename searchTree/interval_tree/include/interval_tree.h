#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H
#include<vector>
using std::vector;
class Interval
{
public:
    // immutable
    Interval(double, double);
    double left() const;
    double right() const;
    bool overlap(const Interval&) const; // whether two interval overlap
    bool inRange(double) const;
private:
    double _left;
    double _right;
};
class IntervalTree
{
public:
    IntervalTree(const vector<Interval>&);
    const IntervalTree* left() const;
    const IntervalTree* right() const;
    bool empty() const;
    double key() const;
    vector<Interval> intervalSearch(const Interval&);
private:
    double middlePoint(const vector<Interval>&);
    void partition(
        const vector<Interval>&,
        double,
        vector<Interval>&,
        vector<Interval>&,
        vector<Interval>&);
    double _key;
    bool _empty;
    IntervalTree* _left;
    IntervalTree* _right;
    vector<Interval> middleLeft;
    vector<Interval> middleRight;
};
#endif
