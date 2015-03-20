#ifndef __SORT_ALGORITHM_H__
#define __SORT_ALGORITHM_H__
#include<vector>
using std::vector;
bool sorted(const vector<int>& vec);
void quickSort(vector<int>& vec,int start, int end);
void quickSortFatPartition(vector<int>& vec,int start, int end);
void newVecQSort(vector<int>& vec);
void mergeSort(vector<int>& vec);
void insertSort(vector<int>&vec);
void bucketSort(vector<int>& vec);
#endif
