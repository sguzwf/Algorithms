#ifndef QSORT_H
#define QSORT_H
#include<vector>
#include<functional>
using std::vector;
using std::function;

template<typename T>
vector<T> qsort(const vector<T>&, const function<bool(const T&,const T&)>&, const function<bool(const T&,const T&)>&);
#endif
