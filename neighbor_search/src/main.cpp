#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<cassert>
#include"SegmentTree.h"
#include"Particle.h"
#define RANGE 1000
#define NUM 10000
#define TESTNUM 100 // number of test case
using namespace std::chrono;
void autoSegmentTreeTest(const StaticSegmentTree& , int);
void genRandPartiles(double, double , double , unsigned int , vector<Particle>& );
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

    auto particles = vector<Particle>();
    genRandPartiles(0, RANGE, 50, 5, particles);

    for(auto v : particles)
    {
        v.printInfo();
    }
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
void genRandPartiles(double leftRange, double rightRange, double maxR, unsigned int particleNum, vector<Particle>& vec)
{
    // assert(vec.empty());
    assert(vec.empty());
    assert(maxR > 0);
    std::default_random_engine gen(std::random_device {}());
    std::uniform_real_distribution<double>distrPos(leftRange, rightRange);
    std::uniform_real_distribution<double>distR(0, maxR);
    vec.reserve(particleNum);
    for (unsigned int i = 0; i < particleNum; i++)
    {
        double randX  = distrPos(gen);
        double randY  = distrPos(gen);
        double randRx = distR(gen);
        double randRy = distR(gen);
        vec.push_back(Particle(randX, randY, randRx, randRy));
    }
}
