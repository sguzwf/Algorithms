#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<cassert>
#include<cstdio>
#include"SegmentTree.h"
#include"Particle.h"
#include"Event.h"
#include"neighborSearch.h"
#define RANGE           1000
#define MAXSEARCHRANGE  50
#define NUM             100000
#define TESTNUM         100 // number of test case
#define MININTERVAL     1
using namespace std::chrono;
using std::vector;
using std::map;
void freeParticles(vector<Particle*> pVec);
int main()
{
    // auto test
    vector<Particle*> pVec;
    pVec.reserve(NUM);
    genRandPartiles(1, RANGE, MAXSEARCHRANGE, NUM, pVec);
    printf("%lu particle generated successfully\n", pVec.size());
    StaticSegmentTree tree = StaticSegmentTree(1, RANGE, MININTERVAL);
    for (auto & v : pVec)
        tree.insert(v);
    printf("%lu paritcles inserted successfully\n", pVec.size());
    if (! autoSegmentTreeTest(tree, TESTNUM, 1, RANGE)) // 测试StaticSegmentTree的插入与query功能
    {
        freeParticles(pVec);
        return EXIT_FAILURE;
    }
    if (! autoEventTest(pVec))
    {
        freeParticles(pVec);
        return EXIT_FAILURE;
    }
    // auto newTree = StaticSegmentTree(1, RANGE, MININTERVAL);
    tree = StaticSegmentTree(1, RANGE, MININTERVAL);

    auto searchResult = map<Particle*, vector<Particle*>>();

    auto t1 = high_resolution_clock::now();
    neighborSearch(pVec, searchResult, tree);
    auto t2 = high_resolution_clock::now();

    auto time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Search Time: " << time_span.count() << " seconds" << std::endl;
    if (! autoTestSearchResult(searchResult))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
void freeParticles(vector<Particle*> pVec)
{
    for (auto p : pVec)
        delete p;
}
