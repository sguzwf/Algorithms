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
    struct AugMiddle
    {
        vector<double> leftEnd;
        vector<double> rightEnd;
    };
private:
    double middlePoint(const vector<Interval>&);
    void partition(
        const vector<Interval>&,
        vector<Interval>&,
        vector<Interval>&,
        vector<Interval>&,
        double);
    double _key;
    bool _empty;
    IntervalTree* _left;
    IntervalTree* _right;
    AugMiddle* _aux;
};
#endif
