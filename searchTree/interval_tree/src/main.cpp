#include<iostream>
#include<vector>
#include<functional>
#include"qsort.h"
using std::vector;
using std::function;
int main()
{
    vector<double> v({3,1,4,1,6});
    function<bool(double,double)> f = std::greater<double>();
    // function<bool(double,double)> f = [](double a, double b){
    //     return a<b;
    // };
    auto vSorted = qsort(v,f);

    for(auto v : vSorted)
    {
        std::cout<<v<<std::endl;
    }
    return 0;
}
