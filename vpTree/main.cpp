#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include"Point.h"
#include"VPTree.h"
using std::cout;
using std::endl;
using namespace std::chrono;
#define RANGEMAX 10
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
    auto t1 = high_resolution_clock::now();
    auto vTree = VPTree(points);
    auto t2 = high_resolution_clock::now();

    double constructionTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "construction time: " << constructionTime << " seconds" << endl;
    return 0;
}
vector<Point> randomPoints(int num)
{
    std::default_random_engine g(0);
    std::uniform_real_distribution<double> d(0, RANGEMAX);
    vector<Point> points;
    points.reserve(num);
    for (decltype(num) i = 0; i < num; i++)
    {
        points.push_back(Point(d(g), d(g), d(g)));
    }
    return points;
}
