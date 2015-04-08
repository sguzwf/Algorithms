#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<cassert>
#include<cstdio>
#include"SegmentTree.h"
#include"Particle.h"
#include"Event.h"
#define RANGE           1000
#define MAXSEARCHRANGE  50
#define NUM             10000
#define TESTNUM         100 // number of test case
#define MININTERVAL     0.1
using namespace std::chrono;
int main()
{
    // auto test
    vector<Particle> vec;
    vec.reserve(NUM);
    genRandPartiles(1, RANGE, MAXSEARCHRANGE, NUM, vec);
    printf("%lu particle generated successfully\n",vec.size());
    auto tree = StaticSegmentTree(1, RANGE, MININTERVAL);
    for (auto & v : vec)
        tree.insert(&v);
    printf("%lu paritcles inserted successfully\n", vec.size());
    autoSegmentTreeTest(tree, TESTNUM, 1, RANGE);
    return 0;
}
