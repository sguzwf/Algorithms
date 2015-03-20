#include<iostream>
#include<vector>
#include<cstdlib>
#include<time.h>
#include<chrono>
#include"./priority_queue.h"
#include"./sort_algorithm.h"
using std::vector;
using namespace std::chrono;

/* #define DISPLAY 1 */

void randomVector(vector<int>& vec);
void displayVec(vector<int>& vec);
void ascendingVector(vector<int>& vec);
void descendingVector(vector<int>& vec);
int main()
{


    srand((unsigned)time(NULL));

    int num = 1000000;
    std::cout<<"Input num"<<std::endl;
    std::cin >> num;
    std::cout<<"num = "<<num<<std::endl;
    
    vector<int> originVec(num,0);
    randomVector(originVec);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Priority_Queue<int>::heapSort(originVec);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2-t1);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, heapSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    randomVector(originVec);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    t1 = high_resolution_clock::now();
    quickSort(originVec,0,originVec.size()-1);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, quickSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;


    randomVector(originVec);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    t1 = high_resolution_clock::now();
    quickSortFatPartition(originVec,0,originVec.size()-1);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, quickSortFatPartition time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    randomVector(originVec);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    t1 = high_resolution_clock::now();
    newVecQSort(originVec);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, quickSort with auxilary vector time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    randomVector(originVec);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    t1 = high_resolution_clock::now();
    mergeSort(originVec);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, mergeSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;


    randomVector(originVec);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    t1 = high_resolution_clock::now();
    bucketSort(originVec);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    #ifdef DISPLAY 
    displayVec(originVec);
    #endif
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, bucketSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    return 0;
}
void ascendingVector(vector<int>& vec)
{
    for(unsigned int i = 0; i < vec.size(); i++)
        vec[i] = i;
}
void descendingVector(vector<int>& vec)
{
    int size = vec.size();
    for(unsigned int i = 0; i < vec.size(); i++)
        vec[i] = size--;
}
void randomVector(vector<int>& vec)
{
    auto size = vec.size();
    for(auto it = vec.begin(); it != vec.end(); it++)
        *it = rand()%size;
}
void displayVec(vector<int>& vec)
{
    for(auto v : vec)
        std::cout<<v<<'\t';
    std::cout<<std::endl;
}
