#include<iostream>
#include<vector>
#include<cassert>
#include"./sort_algorithm.h"
using std::vector;
void swap(int& v1,int& v2)
{
    int tmp = v1;
    v1      = v2;
    v2      = tmp;
}
bool sorted(const vector<int>& vec)
{
    if(vec.size() < 2) return true;
    for(unsigned int i = 1; i < vec.size(); i++)
    {
        if(vec[i] > vec[i-1]) 
        {
            return false;
        }
    }
    return true;
}
void quickSortFatPartition(vector<int>& vec,int start, int end)
{
    //start , end : index of vector
    if(start >= end) return;
    int pivotIdxLeft  = start;
    int pivotIdxRight = start;
    int pivotVal      = vec[pivotIdxRight];
    for(int i = pivotIdxLeft+1; i <= end; i++)
    {
        // values between [pivotidxleft,pivotidxright] are equal to pivotval
        if(i > pivotIdxRight || i < pivotIdxLeft)
        {
            if(vec[i] > pivotVal)
            {
                swap(vec[i],vec[pivotIdxRight+1]);
                swap(vec[pivotIdxRight+1],vec[pivotIdxLeft]);
                pivotIdxLeft++;
                pivotIdxRight++;
            }
            else if(vec[i] == pivotVal)
            {
                swap(vec[i],vec[pivotIdxRight+1]);
                pivotIdxRight++;
            }
        }
        else 
        {
            assert(false);
        }
    }
    quickSortFatPartition(vec,start,pivotIdxLeft-1);
    quickSortFatPartition(vec,pivotIdxRight+1,end);
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
    vec1.reserve(vec.size()/2);
    vec3.reserve(vec.size()/2);
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
void mergeSort(vector<int>& vec)
{
    if(vec.size() <= 1) 
        return;
    if(vec.size() <= 64)
    {
        insertSort(vec);
        return;
    }
    auto size1 = vec.size()/2;
    auto size2 = vec.size() - size1;
    auto vec1  = vector<int>(size1,0);
    auto vec2  = vector<int>(size2,0);
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        if(i < size1) 
            vec1[i] = vec[i];
        else          
            vec2[i-size1] = vec[i];
    }
    mergeSort(vec1);
    mergeSort(vec2);
    unsigned int p1          = 0;
    unsigned int p2          = 0;
    int selectedVec = 0;
    for(unsigned int i = 0; i < vec.size(); i++)
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
void insertSort(vector<int>&vec)
{
    for(unsigned int i = 0; i < vec.size(); i++)
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
void countSort(vector<int>& vec)
{
    if(vec.size() < 2) return;
    int max = vec[0];
    int min = vec[0];
    assert(max >= 0);
    assert(min >= 0);
    for(auto v : vec) // fetch max value O(n)
    {
        if(v > max) max = v;
        if(v < min) min = v;
    }
    auto aux = vector<int>(max-min+1,0);
    for(auto v : vec)
        aux[v-min]++;
    int idx = 0;
    for(int i = aux.size()-1; i >= 0; i--)
    {
        for(int j = 0; j < aux[i]; j++)
            vec[idx++] = i+min;
    }
    /* int bucketSize = 10000; */
    /* int bucketNum  = (max / bucketSize) + 1; */
    /* auto buckets   = vector<vector<int>>(bucketNum,vector<int>()); */
    /* /1* for(auto v : vec) *1/ */
    /* /1*     std::cout<<v<<'\t'; *1/ */
    /* /1* std::cout<<std::endl; *1/ */
    /* /1* std::cout<<"bucketNum = "<<bucketNum<<std::endl; *1/ */

    /* for(auto v : vec) */
    /* { */
    /*     int idx = v / bucketSize; */
    /*     buckets[idx].push_back(v); // maybe we can do insertion here */
    /* } */
    /* for(auto& vvec : buckets) */
    /* { */
    /*     /1* std::cout<<vvec.size()<<std::endl; *1/ */
    /*     mergeSort(vvec); */
    /* } */
    /* int i = 0; */
    /* for(int idx = bucketNum-1; idx >= 0; idx--) */
    /* { */
    /*     for(auto v : buckets[idx]) */
    /*     { */
    /*         vec[i++] = v; */
    /*     } */
    /* } */
}
void bucketSort(vector<int>& vec)
{
    if(vec.size() < 2) return;
    int max = vec[0];
    for(auto v : vec) // fetch max value O(n)
        if(v > max) max = v;
    int bucketSize = 50000;
    int bucketNum  = (max / bucketSize) + 1;
    auto buckets   = vector<vector<int>>(bucketNum,vector<int>());
    for(auto b : buckets)
        b.reserve(bucketSize);
    for(auto v : vec)
    {
        int idx = v / bucketSize;
        buckets[idx].push_back(v); // maybe we can do insertion here
    }
    for(auto& vvec : buckets)
    {
        countSort(vvec);
    }
    int i = 0;
    for(int idx = bucketNum-1; idx >= 0; idx--)
    {
        for(auto v : buckets[idx])
        {
            vec[i++] = v;
        }
    }
}
