#include"qsort.h"
#include<vector>
#include<functional>
#include<random>
using std::vector;
using std::function;
std::default_random_engine g(std::random_device{}());
vector<double> qsort(const vector<double>& input, function<bool(double,double)>& cmp)
{
    auto size = input.size();
    if(size == 0) return input;
    std::uniform_int_distribution<size_t> distr(0,size-1);
    int pivotIdx    = distr(g);
    double pivot    = input[pivotIdx];

    auto vec1 = vector<double>();
    auto vec2 = vector<double>();
    auto vec3 = vector<double>();

    auto result = vector<double>();
    result.reserve(size);
    for(auto v : input)
    {
        if(cmp(v,pivot))
            vec1.push_back(v);
        else if(v == pivot)
            vec2.push_back(v);
        else 
            vec3.push_back(v);
    }
    for(auto v : qsort(vec1,cmp))
        result.push_back(v);
    result.insert(result.end(),vec2.begin(),vec2.end());
    for(auto v : qsort(vec3,cmp))
        result.push_back(v);
    return result;
}
