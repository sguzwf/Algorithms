#include<iostream>
#include<stdio.h>
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
using namespace std::chrono;
#define RANGE_MIN 0
#define RANGE_MAX 1000      // all intervals are in [RANGE_MIN, RANGE_MAX]
#define INTERVAL_NUM 10000   // number of intervals
#define TESTNUM 100         // number test cases
typedef std::default_random_engine stdGen;
typedef std::uniform_real_distribution<double> distr;
int main()
{
    stdGen g(0);
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

    double time_span = 0;
    time_point<high_resolution_clock> start, finish;
    for (int i = 0; i < TESTNUM; i++)
    {
        double edge_1     = d(g);
        double edge_2     = d(g);
        double left_edge  = edge_1 < edge_2 ? edge_1 : edge_2;
        double right_edge = edge_1 < edge_2 ? edge_2 : edge_1;

        auto interv = Interval(left_edge, right_edge);
        start = high_resolution_clock::now();
        auto result = interv_tree.intervalSearch(interv);
        finish = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(finish - start).count();

        for (auto & queried_interv : result)
        {
            if (!interv.overlap(queried_interv))
            {
                std::cout << "fail" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    time_span /= TESTNUM;
    std::cout << TESTNUM << " tests passed" << std::endl;
    std::cout << "interval num: " << INTERVAL_NUM << std::endl;
    std::cout << "average query time: " << time_span << " secondes" << std::endl;

    double inputLeft = RANGE_MIN - 1, inputRight = RANGE_MAX + 1;
    std::cout << "Input Left Range:" << std::endl;
    std::cin >> inputLeft;
    std::cout << "Input Right Range:" << std::endl;
    std::cin >> inputRight;
    auto queryRange = Interval(inputLeft, inputRight);
    auto result = interv_tree.intervalSearch(queryRange);


    int idx = 0;
    for (const auto & interv : result)
    {
        printf("%d.\t[%f,%f]\n", idx++, interv.left(), interv.right());
    }
    printf("length of result:%ld\n", result.size());
    printf("query range: [%f,%f]\n\n", inputLeft, inputRight);
    return 0;
}
