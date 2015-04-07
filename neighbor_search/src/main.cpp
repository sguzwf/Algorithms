#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include"SegmentTree.h"
#include"Particle.h"
#define RANGE 1000
#define NUM 10000
#define TESTNUM 100 // number of test case
using namespace std::chrono;
void autoSegmentTreeTest(const StaticSegmentTree& , int);
int main()
{
    std::default_random_engine engine(std::random_device {}());
    std::uniform_int_distribution<long> distribuition(1, RANGE);
    auto tree = StaticSegmentTree(1, RANGE);
    for (int i = 0; i < NUM; i++)
    {
        tree.insert(distribuition(engine));
    }
    autoSegmentTreeTest(tree, TESTNUM);

    Particle p;
    p.x(3);
    p.y(4);
    p.rx(7);
    p.ry(9);

    auto fuck = p;
    fuck.rx(9);
    fuck.printInfo();
    p.printInfo();
    return 0;
}
void autoSegmentTreeTest(const StaticSegmentTree& stree, int testNum)
{
    std::default_random_engine engine(std::random_device {}());
    long left  = stree.leftRange();
    long right = stree.rightRange();
    std::uniform_int_distribution<long> distribuition(left, right);
    for (int i = 0; i < testNum; i++)
    {
        long leftRandom  = distribuition(engine);
        long maxRange    = right - leftRandom;
        long len         = distribuition(engine) % maxRange;
        long rightRandom = leftRandom + len;
        auto vec         = stree.query(leftRandom, rightRandom);
        for (auto v : vec)
        {
            if (v < leftRandom || v > rightRandom)
            {
                std::cout << "query range: (" << leftRandom << " , " << rightRandom << ")" << std::endl;
                std::cout << "get: " << v << std::endl;
                return;
            }
        }
    }
    std::cout << "passed " << testNum << " test cases" << std::endl;
}
