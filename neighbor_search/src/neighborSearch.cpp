#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#include"Particle.h"
#include"SegmentTree.h"
#include"Event.h"
using std::vector;
using std::map;
void neighborSearch(
    const vector<Particle*>& pVec,
    map<Particle*, vector<Particle*>>& result,
    StaticSegmentTree& tree)
{
    assert(result.empty());
    for (auto p : pVec)
        result[p] = vector<Particle*>();
    auto eVec      = quickSort(genEventVector(pVec));
    double left    = tree.leftRange();
    double right   = tree.rightRange();
    for (auto e : eVec)
    {
        // 不知道 start 类型有什么用……
        auto type         = e.type();
        auto particle     = e.particle();
        double queryLeft  = particle->y() - particle->ry();
        double queryRight = particle->y() + particle->ry();

        // 不能超出query边界
        // 而且边界外肯定没有邻居粒子
        queryLeft  = queryLeft  >= left ?  queryLeft  : left;
        queryRight = queryRight <= right ? queryRight : right;
        switch (type)
        {
        case Event::Start:
            break;
        case Event::Insert:
            tree.insert(particle);
            break;
        case Event::Query:
            auto queryResult = tree.query(queryLeft, queryRight);
            for (auto p : queryResult)
            {
                if (particle->inRange(*p))
                {
                    result[particle].push_back(p);
                }
            }
            break;
        }
    }
}
bool autoTestSearchResult(map<Particle*, vector<Particle*>> searchResult)
{
    // std::cout << "autoTestSearchResult() to be implemented" << std::endl;
    // return false;
    // if this test passed, then you are guaranteed that all particles in value is neighbor of key
    // you still can not be sure that all neighbor of a paritcles found
    // which would be easy to test, but the test procedure would be slow, because you need to examine all particles
    // that is not classified as a particle's neighbor
    for(auto s : searchResult)
    {
        auto key = s.first;
        auto val = s.second;
        for(auto v : val)
        {
            if(! key->inRange(*v))
            {
                std::cout<<"Neighbor Search test Failed"<<std::endl;
                std::cout<<"Query neighbor of this particle:"<<std::endl;
                key->printInfo();
                std::cout<<"Find a particle that is not is neighbor but searched:"<<std::endl;
                v->printInfo();
                return false;
            }
        }
    }
    std::cout<<"Neighbor Search test Passed!"<<std::endl;
    return true;
}
