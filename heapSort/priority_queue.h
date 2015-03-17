#ifndef __PRIORYT_QUEUE_H__
#define __PRIORYT_QUEUE_H__
#include<vector>
using std::vector;

class Priority_Queue
{
    public:
        Priority_Queue();
        Priority_Queue(vector<double>v);
        void insert(double v);
        void updateKey(int idx, double newKey);
        static void heapSort(vector<double>&);
        double extractMin();
        bool isEmpty();
        void displayQ();
    private:
        vector<double>Q;
        void incKey(int idx, double newKey);
        void decKey(int idx, double newKey);
        static int getChildIdxTOSwap(int,vector<double>&,int);
};
#endif
