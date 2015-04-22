#include<iostream>
#include<vector>
#include<cassert>
#include<chrono>
#include<random>
#include<algorithm>
#include"RangeTree.h"
using std::cout;
using std::endl;
using namespace std::chrono;
// #define DEBUG
int main(int num, char** arguments)
{

    // std::default_random_engine g(std::random_device {}());
    // assert(num >= 2);
    int particleNum = atoi(arguments[1]);
    // int particleNum = 9;
    std::default_random_engine g(0);
    std::uniform_real_distribution<double> d(0, RANDMAX);


    Point* points   = new Point[particleNum];
    for (int i = 0; i < particleNum; i++)
    {
        double x = d(g);
        double y = d(g);
        double z = d(g);
        points[i] = Point(x, y, z);
    }
    auto debugVec = vector<Point>(points, points + particleNum);

    auto t1 = high_resolution_clock::now();
    RangeTree rTree(points, 3, particleNum, false);
    auto t2 = high_resolution_clock::now();
    double constructTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "constructTime: " << constructTime << " seconds" << endl;
    cout << "key: " << rTree.key() << endl;

    auto t3 = high_resolution_clock::now();
    double range[3][2] ;
    double radius = 0.1 * RANDMAX;
    for (decltype(particleNum) i = 0; i < particleNum; i++)
    {
        vector<Point> result = vector<Point>();
        vector<Point> result2;
        const Point& pp = points[i];
        range[0][0] = pp.x - radius;
        range[0][1] = pp.x + radius;
        range[1][0] = pp.y - radius;
        range[1][1] = pp.y + radius;
        range[2][0] = pp.z - radius;
        range[2][1] = pp.z + radius;
        rTree.RangeQuery(range, result);
        // auto it = std::copy_if( result.begin(), result.end(), std::back_inserter(result2), [&](const Point& p)->bool{
        //         return pp.inRange(p,radius);
        // });
        result2.reserve(result.size() * 0.7);
        for (const auto & p : result)
        {
            if (pp.inRange(p, radius))
            {
                result2.push_back(p);
            }
        }
    }
    auto t4 = high_resolution_clock::now();
    double queryTime = duration_cast<duration<double>>(t4 - t3).count();
    cout << "queryTime: " << queryTime << " seconds" << endl;

    return 0;
}
