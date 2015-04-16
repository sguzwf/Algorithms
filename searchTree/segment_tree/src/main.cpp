#include<iostream>
#include<stdio.h>
#include<vector>
#include"segment_tree.h"
using std::vector;
using std::cout;
using std::endl;

int main()
{
    SegmentTree sTree(1,10);

    auto vec = sTree.Interval_Insertion(1,9);

    for(auto v : vec)
    {
        printf("[%d,%d]\n", v->rangeLeft(),v->rangeRight());
    }
    cout << "test" << endl;
    return 0;
}
