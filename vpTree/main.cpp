#include<iostream>
#include<vector>
#include<thread>
#include<random>
#include<chrono>
#include<string>
#include<cassert>
#include<algorithm>
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
    int threadNum   = 1;
    if (argNum >= 2)
        particleNum = atoi(args[1]);
    vector<Point> points = randomPoints(particleNum);
    cout << "range max:" << RANGEMAX << endl;
    auto t1 = high_resolution_clock::now();
    auto vTree = VPTree(points);
    auto t2 = high_resolution_clock::now();

    double constructionTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "construction time: " << constructionTime << " seconds" << endl;

    double radius = 0.1 * (double)RANGEMAX;
    cout << "radius: " << radius << endl;
    int pairsum  = 0;
    auto results = vector<vector<Point>>(particleNum);
    auto t3      = high_resolution_clock::now();
    for (decltype(points.size()) i = 0; i < points.size(); i++)
    {
        vTree.search(points[i], radius, results[i]);
    }
    auto t4 = high_resolution_clock::now();
    double searchTime = duration_cast<duration<double>>(t4 - t3).count();
    for (auto & r : results)
        pairsum += r.size();
    cout << "pair sum: " << pairsum << endl;
    cout << "search time: " << searchTime << " seconds" << endl;
    cout << "search + construct: " << (searchTime + constructionTime) << " seconds" << endl;
    cout << "_____________" << endl;

    int directPairNum = 0;
    auto directResult = vector<vector<Point>>(particleNum);
    auto t5 = high_resolution_clock::now();
    for (decltype(points.size()) i = 0; i < points.size(); i++)
    {
        std::copy_if(points.begin(), points.end(), std::back_inserter(directResult[i]), [&](const Point & p1)->bool
        {
            return points[i].inRange(p1, radius);
        });
    }
    auto t6 = high_resolution_clock::now();
    double directSearchTime = duration_cast<duration<double>>(t6 - t5).count();
    cout << "direct search" << endl;
    cout << "pair sum: " << directPairNum << endl;
    cout << "search time: " << directSearchTime << " seconds" << endl;

    double speedup = directSearchTime / (constructionTime + searchTime);
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
