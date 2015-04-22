#include<iostream>
#include<vector>
#include<cassert>
#include<chrono>
#include<random>
#include<omp.h>
#include"RangeTree.h"
using std::cout;
using std::endl;
using namespace std::chrono;
// #define DEBUG
int main(int num, char** arguments)
{

    // std::default_random_engine g(std::random_device {}());
    std::default_random_engine g(0);
    std::uniform_real_distribution<double> d(0, RANDMAX);
    int particleNum = atoi(arguments[1]);
    Point* points = new Point[particleNum];
    omp_set_num_threads(1);
    for (int i = 0; i < particleNum; i++)
    {
        double x = d(g);
        double y = d(g);
        double z = d(g);
        points[i] = Point(x, y, z);
    }

    // Point* points = new Point[particleNum];
    // points[0] = Point(0.5,0.5,0.5);
    // points[1] = Point(1.5,1.5,1.5);
    auto t1 = high_resolution_clock::now();
    RangeTree rTree(points, 3, particleNum, false);
    auto t2 = high_resolution_clock::now();
    double constructTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "constructTime: " << constructTime << " seconds" << endl;
    cout << "key: " << rTree.key() << endl;

    auto t3 = high_resolution_clock::now();
    double range[3][2] ;
    double radius = 3;
#pragma omp parallel for
    for (decltype(particleNum) i = 0; i < particleNum; i++)
    {
        vector<Point> result = vector<Point>();
        vector<Point> result2 = vector<Point>();
        const Point& pp = points[i];
        range[0][0] = pp.x - radius;
        range[0][1] = pp.x + radius;
        range[1][0] = pp.y - radius;
        range[1][1] = pp.y + radius;
        range[2][0] = pp.z - radius;
        range[2][1] = pp.z + radius;
        rTree.RangeQuery(range, result);
        for (const auto & p : result)
        {
            // if (fabs(p.x - pp.x) > radius)
            // {
            //     cout << "x confilction" << endl;
            //     cout << "radius: " << radius << endl;
            //     p.printPoint();
            //     pp.printPoint();
            //     assert(0);
            // }
            // if (fabs(p.y - pp.y) > radius)
            // {
            //     cout << "y confilction" << endl;
            //     cout << "radius: " << radius << endl;
            //     p.printPoint();
            //     pp.printPoint();
            //     assert(0);
            // }
            // if (fabs(p.z - pp.z) > radius)
            // {
            //     cout << "z confilction" << endl;
            //     cout << "radius: " << radius << endl;
            //     p.printPoint();
            //     pp.printPoint();
            //     assert(0);
            // }
            if ((p.x - pp.x) * (p.x - pp.x) + (p.y - pp.y) * (p.y - pp.y) + (p.z - pp.z) * (p.z - pp.z) <= radius * radius)
            {
                result2.push_back(p);
            }
        }
        // cout << result2.size() << endl;
    }
    auto t4 = high_resolution_clock::now();
    double queryTime = duration_cast<duration<double>>(t4 - t3).count();
    cout << "queryTime: " << queryTime << " seconds" << endl;

    return 0;
}
