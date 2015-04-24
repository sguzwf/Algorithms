#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<string>
#include<cassert>
#include<omp.h>
#include"Point.h"
#include"VPTree.h"
using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono;

#define RANGEMAX 10
#ifdef NDEBUG
std::default_random_engine g(std::random_device {}());
#else
std::default_random_engine g(0);
#endif

std::uniform_real_distribution<double> d(0, RANGEMAX);
vector<Point> randomPoints(int);

int main(int argNum, char** args)
{
    int particleNum = 4;
    if (argNum >= 2)
        particleNum = atoi(args[1]);
    vector<Point> points = randomPoints(particleNum);
    // for (const auto & p : points)
    //     p.printPoint();
    // cout << "-----------------" << endl;
    cout << "range max:" << RANGEMAX << endl;
    auto t1 = high_resolution_clock::now();
    auto vTree = VPTree(points);
    auto t2 = high_resolution_clock::now();

    double constructionTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "construction time: " << constructionTime << " seconds" << endl;

    double radius = 0.1619 * (double)RANGEMAX;
    int pairsum   = 0;
    cout << "radius: " << radius << endl;
    auto results = vector<vector<Point>>(particleNum);
    auto t3 = high_resolution_clock::now();
    // for (const auto & p : points)
#pragma omp parallel for
    for (decltype(points.size()) i = 0; i < points.size(); i++)
    {
        vTree.search(points[i], radius, results[i]);
    }
    auto t4 = high_resolution_clock::now();
    double searchTime = duration_cast<duration<double>>(t4 - t3).count();
    for(auto& r : results)
        pairsum += r.size();
    cout << "pair sum: " << pairsum << endl;
    cout << "search time: " << searchTime << " seconds" << endl;
    cout << "_____________" << endl;

    int directPairNum = 0;
    auto directResult = vector<vector<Point>>(particleNum);
    auto t5 = high_resolution_clock::now();
    // for(const auto& p1 : points)
    for (decltype(points.size()) i = 0; i < points.size(); i++)
    {
        for (const auto & p : points)
        {
            double dist = points[i].distance(p);
            if (0 < dist && dist <= radius)
            {
                directResult[i].push_back(p);
            }
        }
        directPairNum += directResult[i].size();
    }
    auto t6 = high_resolution_clock::now();
    double directSearchTime = duration_cast<duration<double>>(t6 - t5).count();
    cout << "direct search" << endl;
    cout << "pair sum: " << directPairNum << endl;
    cout << "search time: " << directSearchTime << " seconds" << endl;

    double speedup = directSearchTime / searchTime;
    cout << "speedup: " << speedup << endl;
    return 0;
}
vector<Point> randomPoints(int num)
{
    vector<Point> points;
    points.reserve(num);
    for (decltype(num) i = 0; i < num; i++)
    {
        points.push_back(Point(d(g), d(g), d(g)));
    }
    return points;
}
