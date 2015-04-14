#include<iostream>
#include<vector>
#include<functional>
#include<chrono>
#include<random>
#include<utility>
#include"interval_tree.h"
#include"qsort.h"
using std::vector;
using std::function;
using std::pair;
#define RANGE_MIN 0
#define RANGE_MAX 1000      // all intervals are in [RANGE_MIN, RANGE_MAX]
#define INTERVAL_NUM 1000   // number of intervals
#define TESTNUM 100         // number test cases
typedef std::default_random_engine stdGen;
typedef std::uniform_real_distribution<double> distr;
int main()
{
    stdGen g(std::random_device {}());
    distr  d(RANGE_MIN, RANGE_MAX);

    auto interval_vec = vector<Interval>();
    interval_vec.reserve(INTERVAL_NUM);
    for (int i = 0; i < INTERVAL_NUM; i++)
    {
        double edge_1     = d(g);
        double edge_2     = d(g);
        double left_edge  = edge_1 < edge_2 ? edge_1 : edge_2;
        double right_edge = edge_1 < edge_2 ? edge_2 : edge_1;
        interval_vec.push_back(Interval(left_edge, right_edge));
    }
    IntervalTree interv_tree(interval_vec);

    for (int i = 0; i < TESTNUM; i++)
    {
        double edge_1     = d(g);
        double edge_2     = d(g);
        double left_edge  = edge_1 < edge_2 ? edge_1 : edge_2;
        double right_edge = edge_1 < edge_2 ? edge_2 : edge_1;

        auto interv = Interval(left_edge, right_edge);
        auto result = interv_tree.intervalSearch(interv);

        for (auto & queried_interv : result)
        {
            if (!interv.overlap(queried_interv))
            {
                std::cout<<"fail"<<std::endl;
            }
        }
    }
    return 0;
}
