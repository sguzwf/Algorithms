#include<vector>
#include<type_traits>
#include<cassert>
#include<functional>
#include<iostream>
#include"./priority_queue.h"
using std::vector;
using std::function;

Priority_Queue::Priority_Queue()
    :Q(vector<double>())
{
}
Priority_Queue::Priority_Queue(vector<double> vec)
    :Q(vector<double>(vec.size(),0))
{
    int size = vec.size();
    int len  = 0;
    double tmp  = 0;
    for(auto val : vec)
    {
        int idx       = len;
        int parentIdx = (len-1)/2;
        Q[idx]        = val;
        while(idx > 0 && Q[idx] < Q[parentIdx])
        {
            tmp          = Q[idx];
            Q[idx]       = Q[parentIdx];
            Q[parentIdx] = tmp;
            idx          = parentIdx;
            parentIdx    = (idx-1)/2;
        }
        len++;
    }
}
void Priority_Queue::insert(double v)
{
    Q.push_back(v);
    int size = Q.size();
    int idx  = size-1;
    int pIdx = (idx-1)/2;
    
    double tmp = 0;
    while(Q[idx] < Q[pIdx] && idx > 0)
    {
        tmp     = Q[idx];
        Q[idx]  = Q[pIdx];
        Q[pIdx] = tmp;
        idx     = pIdx;
        pIdx    = (idx-1)/2;
    }
}
void Priority_Queue::updateKey(int idx, double newKey)
{
    int size = Q.size();
    assert(idx < size);
    auto oldKey = Q[idx];
    if(oldKey == newKey) 
        return;
    else if(oldKey < newKey)
        incKey(idx,newKey);
    else 
        decKey(idx,newKey);
}
double Priority_Queue::extractMin()
{
    assert(!Q.empty());
    double top     = Q[0];
    double lastEle = Q.back();
    Q.pop_back();
    if(!Q.empty())
        incKey(0,lastEle);
    return top;
}
bool Priority_Queue::isEmpty()
{
    return Q.empty();
}
int Priority_Queue::getChildIdxTOSwap(int id, vector<double>& vec, int size)
{
    int retIdx = id;
    assert(size <= (int)vec.size());
    int c1Idx  = 2 * id + 1;
    int c2Idx  = 2* id + 2;
    if(c1Idx < size && vec[retIdx] > vec[c1Idx])
        retIdx = c1Idx;
    if(c2Idx < size && vec[retIdx] > vec[c2Idx])
        retIdx = c2Idx;
    return retIdx;
}
void Priority_Queue::incKey(int idx, double newKey)
{
    // bubble down
    int size   = Q.size();
    int oldKey = Q[idx];
    assert(idx < size);
    assert(oldKey <= newKey);
    Q[idx] = newKey;
    int cIdxToSwap = getChildIdxTOSwap(idx,Q,size);
    double tmp = 0;
    while(cIdxToSwap != idx)
    {
        tmp           = Q[idx];
        Q[idx]        = Q[cIdxToSwap];
        Q[cIdxToSwap] = tmp;
        idx           = cIdxToSwap;
        cIdxToSwap    = getChildIdxTOSwap(idx,Q,size);
    }
}
void Priority_Queue::decKey(int idx, double newKey)
{
    int size   = Q.size();
    int pIdx   = (idx-1)/2;
    Q[idx]     = newKey;
    double tmp = 0;
    while(idx > 0 && Q[idx] < Q[pIdx])
    {
        tmp     = Q[idx];
        Q[idx]  = Q[pIdx];
        Q[pIdx] = tmp;
        idx     = pIdx;
        pIdx    = (idx-1)/2;
    }
}

void Priority_Queue::heapSort(vector<double>& vec)
{
    int size = vec.size();
    int len  = 0;
    
    // construct heap 
    double tmp = 0;
    for(int i = 0; i < size; i++)
    {
        int idx  = i;
        int pIdx = (idx-1)/2;
        //root ele has highest key
        while(idx > 0 && vec[idx] < vec[pIdx])
        {
            tmp       = vec[idx];
            vec[idx]  = vec[pIdx];
            vec[pIdx] = tmp;
            idx       = pIdx;
            pIdx      = (idx-1)/2;
        }
    }

    // generate sorted vector
    for(int i = size-1; i >= 0; i--)
    {
        //swap root element
        tmp    = vec[i];
        vec[i] = vec[0];
        vec[0] = tmp;

        // bubble down root element
        int idx     = 0;
        int swapIdx = getChildIdxTOSwap(idx,vec,i);
        while(idx != swapIdx)
        {
            tmp          = vec[idx];
            vec[idx]     = vec[swapIdx];
            vec[swapIdx] = tmp;
            idx          = swapIdx;
            swapIdx      = getChildIdxTOSwap(idx,vec,i);
        }

    }
}
void Priority_Queue::displayQ()
{
    for(auto v : Q)
        std::cout<<v<<std::endl;
}
