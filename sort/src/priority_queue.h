#ifndef __PRIORYT_QUEUE_H__
#define __PRIORYT_QUEUE_H__
#include<iostream>
#include<vector>
#include<cassert>
using std::vector;

template<typename Real>
class Priority_Queue
{
    public:
        Priority_Queue();
        Priority_Queue(vector<Real>v);
        void insert(Real v);
        void updateKey(int idx, Real newKey);
        static void heapSort(vector<Real>&);
        Real extractMin();
        bool isEmpty();
        void displayQ();
    private:
        vector<Real>Q;
        void incKey(int idx, Real newKey);
        void decKey(int idx, Real newKey);
        static int getChildIdxTOSwap(int,vector<Real>&,int);
};
template<typename Real>
Priority_Queue<Real>::Priority_Queue()
{
}
template<typename Real>
Priority_Queue<Real>::Priority_Queue(vector<Real> vec)
    :Q(vector<Real>(vec.size(),0))
{
    int size = vec.size();
    int len  = 0;
    Real tmp  = 0;
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
template<typename Real>
void Priority_Queue<Real>::insert(Real v)
{
    Q.push_back(v);
    int size = Q.size();
    int idx  = size-1;
    int pIdx = (idx-1)/2;
    
    Real tmp = 0;
    while(Q[idx] < Q[pIdx] && idx > 0)
    {
        tmp     = Q[idx];
        Q[idx]  = Q[pIdx];
        Q[pIdx] = tmp;
        idx     = pIdx;
        pIdx    = (idx-1)/2;
    }
}
template<typename Real>
void Priority_Queue<Real>::updateKey(int idx, Real newKey)
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
template<typename Real>
Real Priority_Queue<Real>::extractMin()
{
    assert(!Q.empty());
    Real top     = Q[0];
    Real lastEle = Q.back();
    Q.pop_back();
    if(!Q.empty())
        incKey(0,lastEle);
    return top;
}
template<typename Real>
bool Priority_Queue<Real>::isEmpty()
{
    return Q.empty();
}
template<typename Real>
int Priority_Queue<Real>::getChildIdxTOSwap(int id, vector<Real >& vec, int size)
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
template<typename Real>
void Priority_Queue<Real>::incKey(int idx, Real newKey)
{
    // bubble down
    int size   = Q.size();
    int oldKey = Q[idx];
    assert(idx < size);
    assert(oldKey <= newKey);
    Q[idx] = newKey;
    int cIdxToSwap = getChildIdxTOSwap(idx,Q,size);
    Real tmp = 0;
    while(cIdxToSwap != idx)
    {
        tmp           = Q[idx];
        Q[idx]        = Q[cIdxToSwap];
        Q[cIdxToSwap] = tmp;
        idx           = cIdxToSwap;
        cIdxToSwap    = getChildIdxTOSwap(idx,Q,size);
    }
}
template<typename Real>
void Priority_Queue<Real>::decKey(int idx, Real newKey)
{
    int size   = Q.size();
    int pIdx   = (idx-1)/2;
    Q[idx]     = newKey;
    Real tmp = 0;
    while(idx > 0 && Q[idx] < Q[pIdx])
    {
        tmp     = Q[idx];
        Q[idx]  = Q[pIdx];
        Q[pIdx] = tmp;
        idx     = pIdx;
        pIdx    = (idx-1)/2;
    }
}

template<typename Real>
void Priority_Queue<Real>::heapSort(vector<Real >& vec)
{
    int size = vec.size();
    // construct heap 
    Real tmp = 0;
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
template<typename Real>
void Priority_Queue<Real>::displayQ()
{
    for(auto v : Q)
        std::cout<<v<<std::endl;
}
#endif
