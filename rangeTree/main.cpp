#include<iostream>
#include<vector>
#include<cassert>
#include<chrono>
#include<random>
#include<algorithm>
#include"RangeTree.h"
#include<array>
using std::cout;
using std::endl;
using namespace std::chrono;
using std::array;
// #define DEBUG
int main(int num, char** arguments)
{

    // std::default_random_engine g(std::random_device {}());
    // assert(num >= 2);
    int particleNum = atoi(arguments[1]);
    // int particleNum = 23;
    int seed = 0;
    cout << "seed: " << seed << endl;
    std::default_random_engine g(seed);
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

    double range[3][2] ;
    double radius = 0.4 * RANDMAX;
    vector<vector<Point>>searchResult(particleNum);
    auto t3 = high_resolution_clock::now();
    for (decltype(particleNum) i = 0; i < particleNum; i++)
    {
        const Point& pp = points[i];
        range[0][0] = pp.x - radius;
        range[0][1] = pp.x + radius;
        range[1][0] = pp.y - radius;
        range[1][1] = pp.y + radius;
        range[2][0] = pp.z - radius;
        range[2][1] = pp.z + radius;
        // vector<Point> result2;
        vector<Point> result = vector<Point>();
        rTree.RangeQuery(range, result);
        // result2.reserve(result.size() * 0.7);
        searchResult[i].reserve(result.size());
        std::copy_if( result.begin(), result.end(), std::back_inserter(searchResult[i]), [&](const Point & p)->bool
        {
            return pp.inRange(p, radius);
        });
    }
    auto t4 = high_resolution_clock::now();
    double queryTime = duration_cast<duration<double>>(t4 - t3).count();
    cout << "queryTime: " << queryTime << " seconds" << endl;

    auto t5 = high_resolution_clock::now();
    vector<vector<Point>>directSearchResult(particleNum);
    for (decltype(particleNum) i = 0; i < particleNum; i++)
    {
        const Point& pp = points[i];
        std::copy_if( points, points + particleNum, std::back_inserter(directSearchResult[i]), [&](const Point & p)->bool
        {
            return pp.inRange(p, radius);
        });
    }
    auto t6 = high_resolution_clock::now();
    double directQueryTime = duration_cast<duration<double>>(t6 - t5).count();
    cout << "directQueryTime: " << directQueryTime << " seconds" << endl;

    int errNum = 0;
    for (decltype(particleNum) i = 0; i < particleNum; i++)
    {
        if (searchResult[i].size() != directSearchResult[i].size())
        {
            errNum ++;
            cout << "searchResult["         << i << "]= " << searchResult[i].size()         << endl;
            cout << "directSearchResult["   << i << "]= " << directSearchResult[i].size()   << endl;
            points[i].printPoint();
            cout << "result of search:" << endl;
            for(auto p : searchResult[i])
                p.printPoint();
            cout << "********" << endl;
            cout << "result of direct search:" << endl;
            for(auto p : directSearchResult[i])
                p.printPoint();
            cout << "_________" << endl;

        }
    }
    cout << "errNum: " << errNum << endl;
    return 0;
}
