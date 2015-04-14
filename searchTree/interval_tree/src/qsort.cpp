#include"qsort.h"
#include<vector>
#include<functional>
#include<random>
#include"interval_tree.h"
using std::vector;
using std::function;
std::default_random_engine g(std::random_device{}());


template<typename T>
vector<T> qsort(
        const vector<T>& input,
        const function<bool(const T&,const T&)>& lessThan,
        const function<bool(const T&,const T&)>& equal
        )
{
    auto size = input.size();
    if(size == 0) return input;
    std::uniform_int_distribution<size_t> distr(0,size-1);
    int pivotIdx    = distr(g);
    T pivot    = input[pivotIdx];

    auto vec1 = vector<T>();
    auto vec2 = vector<T>();
    auto vec3 = vector<T>();

    auto result = vector<T>();
    result.reserve(size);
    for(auto v : input)
    {
        if(lessThan(v,pivot))
            vec1.push_back(v);
        else if(equal(v,pivot))
            vec2.push_back(v);
        else 
            vec3.push_back(v);
    }
    for(auto v : qsort(vec1,lessThan,equal))
        result.push_back(v);
    result.insert(result.end(),vec2.begin(),vec2.end());
    for(auto v : qsort(vec3,lessThan,equal))
        result.push_back(v);
    return result;
}
template vector<Interval> qsort(
        const vector<Interval>&,
        const function<bool(const Interval&,const Interval&)>&, 
        const function<bool(const Interval&,const Interval&)>&
        );
// template vector<double> qsort(const vector<double>&, const function<bool(double&,double&)>&, const function<bool(double&,double&)>&);
