#include<iostream>
#include<vector>
#include<cassert>
#include<chrono>
#include<random>
#include"RangeTree.h"
using std::cout;
using std::endl;
using namespace std::chrono;
int main(int num, char** arguments)
{
    int particleNum = atoi(arguments[1]);
    // int particleNum = 4;

    // std::default_random_engine g(std::random_device {}());
    std::default_random_engine g(0);
    std::uniform_real_distribution<double> d(0, RANDMAX);
    Point* points = new Point[particleNum];
    for (int i = 0; i < particleNum; i++)
    {
        double x = d(g);
        double y = d(g);
        double z = d(g);
        points[i] = Point(x,y,z);
    }
    // for(int i = 0; i < particleNum; i++)
    // {
    //     cout<<"("<<points[i].x<<" , "<<points[i].y<<" , "<<points[i].z<<")"<<endl;
    // }
    auto t1 = high_resolution_clock::now();
    RangeTree rTree(points, 3,particleNum,false);
    auto t2 = high_resolution_clock::now();
    double constructTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "constructTime: " << constructTime << " seconds" << endl;
    cout << "key: " << rTree.key() << endl;
    return 0;
}
