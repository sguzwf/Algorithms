#include<iostream>
#include<vector>
#include<cstdlib>
#include<time.h>
#include<chrono>
#include"./priority_queue.h"
#include<stdio.h>
using std::vector;
using namespace std::chrono;
/* #define DISPLAY 1 */

void randomVector(vector<int>& vec);
void displayVec(vector<int>& vec);
void quickSort(vector<int>& vec,int start, int end);
void ascendingVector(vector<int>& vec);
void descendingVector(vector<int>& vec);
bool sorted(const vector<int>& vec);
void newVecQSort(vector<int>& vec);
void mergeSort(vector<int>& vec);
void insertSort(vector<int>&vec);
void bucketSort(vector<int>& vec);
int main()
{


    srand((unsigned)time(NULL));

    int num = 1000000;
    std::cout<<"Input num"<<std::endl;
    std::cin >> num;
    std::cout<<"num = "<<num<<std::endl;
    
    vector<int> originVec(num,0);
    randomVector(originVec);
    displayVec(originVec);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Priority_Queue<int>::heapSort(originVec);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2-t1);
    displayVec(originVec);
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, heapSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    randomVector(originVec);
    displayVec(originVec);
    t1 = high_resolution_clock::now();
    quickSort(originVec,0,originVec.size()-1);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    displayVec(originVec);
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, quickSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    randomVector(originVec);
    displayVec(originVec);
    t1 = high_resolution_clock::now();
    newVecQSort(originVec);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    displayVec(originVec);
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, new quickSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    randomVector(originVec);
    displayVec(originVec);
    t1 = high_resolution_clock::now();
    mergeSort(originVec);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    displayVec(originVec);
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, mergeSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;


    randomVector(originVec);
    displayVec(originVec);
    t1 = high_resolution_clock::now();
    bucketSort(originVec);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2-t1);
    displayVec(originVec);
    if(sorted(originVec)) 
        std::cout<<"sorted"<<std::endl;
    std::cout<<"random vector, bucketSort time consumed:"<<time_span.count()<<" seconds"<<std::endl;
    std::cout<<"--------------------------"<<std::endl;

    /* randomVector(originVec); */
    /* displayVec(originVec); */
    /* t1 = high_resolution_clock::now(); */
    /* insertSort(originVec); */
    /* t2 = high_resolution_clock::now(); */
    /* time_span = duration_cast<duration<double>>(t2-t1); */
    /* displayVec(originVec); */
    /* if(sorted(originVec)) */ 
    /*     std::cout<<"sorted"<<std::endl; */
    /* std::cout<<"random vector, insertSort time consumed:"<<time_span.count()<<" seconds"<<std::endl; */
    /* std::cout<<"--------------------------"<<std::endl; */
    return 0;
}
void ascendingVector(vector<int>& vec)
{
    for(int i = 0; i < vec.size(); i++)
        vec[i] = i;
}
void descendingVector(vector<int>& vec)
{
    int size = vec.size();
    for(int i = 0; i < vec.size(); i++)
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
#ifdef DISPLAY
    for(auto v : vec)
        std::cout<<v<<'\t';
    std::cout<<std::endl;
#endif
}
#define DISPLAY
void newVecQSort(vector<int>& vec)
{
    //use firste element as pivot
    bool sorted(const vector<int>&);
    if(vec.size() < 2) return;
    int pivotIdx = 0;
    int pivot    = vec[pivotIdx];
    int size     = vec.size();
    vector<int> vec1    = vector<int>();
    vector<int> vec2    = vector<int>();
    vector<int> vec3    = vector<int>();
    for(auto v : vec)
    {
        if(v > pivot)       vec1.push_back(v);
        else if(v == pivot) vec2.push_back(v);
        else if(v < pivot)  vec3.push_back(v);
    }
    newVecQSort(vec1);
    newVecQSort(vec3);
    int idx = 0;
    for(auto v : vec1)
        vec[idx++] = v;
    for(auto v : vec2)
        vec[idx++] = v;
    for(auto v : vec3)
        vec[idx++] = v;
    assert(size == idx);
}
void quickSort(vector<int>& vec,int start, int end)
{
    //start , end : index of vector
    if(start >= end) return;
    /* assert(end < vec.size()); */
    int pivotIdx = start;
    int tmp      = 0;
    for(int i = pivotIdx+1; i <= end; i++)
    {
        if(vec[i] > vec[pivotIdx])
        {
            tmp             = vec[i];
            vec[i]          = vec[pivotIdx+1];
            vec[pivotIdx+1] = tmp;

            tmp             = vec[pivotIdx];
            vec[pivotIdx]   = vec[pivotIdx+1];
            vec[pivotIdx+1] = tmp;

            pivotIdx++;
        }
    }
    /* displayVec(vec); */
    /* std::cout<<"pivotIdx = "<<pivotIdx<<std::endl; */
    quickSort(vec,start,pivotIdx-1);
    quickSort(vec,pivotIdx+1,end);
}
void mergeSort(vector<int>& vec)
{
    if(vec.size() <= 1) 
        return;
    if(vec.size() <= 64)
    {
        insertSort(vec);
        return;
    }
    int size1 = vec.size()/2;
    int size2 = vec.size() - size1;
    auto vec1 = vector<int>(size1,0);
    auto vec2 = vector<int>(size2,0);
    for(int i = 0; i < vec.size(); i++)
    {
        if(i < size1) 
            vec1[i] = vec[i];
        else          
            vec2[i-size1] = vec[i];
    }
    mergeSort(vec1);
    mergeSort(vec2);
    int p1          = 0;
    int p2          = 0;
    int selectedVec = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(p1 == vec1.size() && p2 == vec2.size())
            assert(i == vec.size()-1);
        else if(p1 == vec1.size())
            selectedVec = 2;
        else if(p2 == vec2.size())
            selectedVec = 1;
        else if(vec1[p1] < vec2[p2])
            selectedVec = 2;
        else 
            selectedVec = 1;
        switch(selectedVec)
        {
            case 1:
                vec[i] = vec1[p1];
                p1++;
                break;
            case 2:
                vec[i] = vec2[p2];
                p2++;
                break;
            default:
                assert(i == vec.size()-1);
        }
    }
}
bool sorted(const vector<int>& vec)
{
    if(vec.size() < 2) return true;
    for(int i = 1; i < vec.size(); i++)
    {
        if(vec[i] > vec[i-1]) 
        {
            for(auto v : vec)
                std::cout<<v<<'\t';
            std::cout<<std::endl;
            printf("vec[%d]=%d\nvec[%d]=%d\n",i,vec[i],i-1,vec[i-1]);
            return false;
        }
    }
    return true;
}
void insertSort(vector<int>&vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        int val = vec[i];
        for(int j = i-1; j >= 0; j--)
        {
            if(val > vec[j])
            {
                vec[j+1] = vec[j];
                vec[j] = val;
            }
        }
    }
}
void bucketSort(vector<int>& vec)
{
    if(vec.empty()) return;
    int max = vec[0];
    for(auto v : vec) // fetch max value O(n)
        if(v > max) max = v;
    int bucketSize = 1;
    int bucketNum  = (max / bucketSize) + 1;
    auto buckets   = vector<vector<int>>(bucketNum,vector<int>());
    /* for(auto v : vec) */
    /*     std::cout<<v<<'\t'; */
    /* std::cout<<std::endl; */
    /* std::cout<<"bucketNum = "<<bucketNum<<std::endl; */

    for(auto v : vec)
    {
        int idx = v / bucketSize;
        buckets[idx].push_back(v); // maybe we can do insertion here
    }
    /* int avgBucketLen = 0; */
    /* for(auto& vvec : buckets) */
    /* { */
    /*     avgBucketLen += vvec.size(); */
    /*     mergeSort(vvec); */
    /* } */
    /* avgBucketLen /= bucketNum; */
    /* std::cout<<"average bucket length:"<<avgBucketLen<<std::endl; */
    /* std::cout<<"bucketNum"<<bucketNum<<std::endl; */
    int i = 0;
    for(int idx = bucketNum-1; idx >= 0; idx--)
    {
        for(auto v : buckets[idx])
        {
            vec[i++] = v;
        }
    }
}
