#ifndef QSORT_H
#define QSORT_H
#include<vector>
#include<functional>
using std::vector;
using std::function;
vector<double> qsort(const vector<double>&, function<bool(double,double)>&);
#endif
