#include<iostream>
#include<cstdio>
#include<vector>
#include<list>
#include<cassert>
#include<chrono>
#include<random>
#include<cmath>
#include<algorithm>
#include"global_def.h"
using namespace std;
using namespace std::chrono;
double* randomDoubleArr(unsigned int);
void partialSelectonSort(double* arr, unsigned int size, unsigned int index);
void quickSelect(double* arr, unsigned int size, unsigned int k);
bool check(double* arr, int size, int k);
void quickSelectIter(double* arr, unsigned int size, unsigned int k);
int main(int argNum, char** args)
{
    unsigned int num = 10;
    if (argNum > 1)
        num = atoi(args[1]);
    cout << "num of number: " << num << endl;
    double* const arr1 = randomDoubleArr(num);
    double* const arr2 = randomDoubleArr(num);
    double* const arr3 = randomDoubleArr(num);
    double* const arr4 = randomDoubleArr(num);
    unsigned int k = num / 2;
    if (argNum > 2)
        k = atoi(args[2]);
    printf("k = %d\n", k);
    auto t1 = high_resolution_clock::now();
    partialSelectonSort(arr1, num, k);
    auto t2 = high_resolution_clock::now();
    bool checkPartial = check(arr1, num, k);
    double tPartialSelect = duration_cast<duration<double>>(t2 - t1).count();
    cout << "checkPartial: " << checkPartial << endl;
    cout << "time of partialSelectonSort: " << tPartialSelect << endl;
    cout << "______________________" << endl;

    auto t3 = high_resolution_clock::now();
    quickSelect(arr2, num, k);
    auto t4 = high_resolution_clock::now();
    bool checkQuick = check(arr2, num, k);
    double tQuickSelect = duration_cast<duration<double>>(t4 - t3).count();
    cout << "checkQuick: " << checkQuick << endl;
    cout << "time of quickSelect: " << tQuickSelect << endl;
    cout << "______________________" << endl;

    auto t5 = high_resolution_clock::now();
    std::nth_element(arr3, arr3 + k - 1, arr3 + num);
    auto t6 = high_resolution_clock::now();
    bool checkNth = check(arr3, num, k);
    double tCheckNth = duration_cast<duration<double>>(t6 - t5).count();
    cout << "checkNth: " << checkNth << endl;
    cout << "tCheckNth: " << tCheckNth << endl;
    cout << "______________________" << endl;

    auto t7 = high_resolution_clock::now();
    quickSelectIter(arr4, num, k);
    auto t8 = high_resolution_clock::now();
    bool checkQuickIter = check(arr4, num, k);
    double tQuickSelectIter = duration_cast<duration<double>>(t8 - t7).count();
    cout << "checkQuickIter: " << checkQuickIter << endl;
    cout << "tQuickSelectIter: " << tQuickSelectIter << endl;
    delete[] arr1;
    delete[] arr2;
    return 0;
}
double* randomDoubleArr(unsigned int num)
{
    double* const arr = new double[num];
    for (decltype(num) i = 0; i < num; i++)
    {
        arr[i] = d(g);
    }
    return arr;
}
void partialSelectonSort(double* arr, unsigned int size, unsigned int k)
{
    if (size >= 1000000)
    {
        cout << "array too large" << endl;
        return;
    }
    for (unsigned int i = 0; i < k; i++)
    {
        unsigned int minIdx   = i;
        double       minValue = arr[i];
        for (decltype(i) j = i + 1; j < size; j++)
        {
            if (arr[j] < minValue)
            {
                minIdx   = j;
                minValue = arr[j];
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
void quickSelect(double* arr, unsigned int size, unsigned int k)
{
    if (size <= 1) return;
    std::uniform_int_distribution<unsigned int> d(0, size - 1);
    std::swap(arr[0], arr[d(g)]);
    unsigned int pivotIdx = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (arr[i] < arr[pivotIdx] && i > pivotIdx)
        {
            swap(arr[pivotIdx + 1], arr[i]);
            swap(arr[pivotIdx], arr[pivotIdx + 1]);
            pivotIdx++;
        }
    }
    if (pivotIdx > k)
        quickSelect(arr, pivotIdx, k);
    else if (pivotIdx < k)
        quickSelect(arr + pivotIdx, size - pivotIdx, k - pivotIdx);
    else
        return;
}
void quickSelectIter(double* arr, unsigned int size, unsigned int k)
{
    decltype(k) startIdx = 0;
    decltype(k) endIdx   = size;
    while (1)
    {
        if (endIdx - startIdx <= 1) break;
        decltype(k) randIdx  = uniform_int_distribution<decltype(k)>(startIdx, endIdx - 1)(g);
        swap(arr[startIdx], arr[randIdx]);
        decltype(k) pivotIdx = startIdx;
        for (decltype(pivotIdx) i = startIdx; i < endIdx; i++)
        {
            if (arr[i] < arr[pivotIdx] && i > pivotIdx)
            {
                swap(arr[i], arr[pivotIdx + 1]);
                swap(arr[pivotIdx], arr[pivotIdx + 1]);
                pivotIdx++;
            }
        }
        if (pivotIdx == k - 1)
            break;
        else if (pivotIdx + 1 < k)
            startIdx = pivotIdx + 1;
        else
            endIdx = pivotIdx;
    }
}
bool check(double* arr, int size, int k)
{
    if (k > size) return false;
    for (int i = 0; i < size; i++)
    {
        if (i < k - 1 && arr[i] > arr[k - 1])
        {
            printf("left half: a[%d] = %f, a[%d] = %f\n", i, arr[i], k - 1, arr[k - 1]);
            return false;
        }
        else if (i > k - 1 && arr[i] < arr[k - 1])
        {
            printf("right half: a[%d] = %f, a[%d] = %f\n", i, arr[i], k - 1, arr[k - 1]);
            return false;
        }
    }
    return true;
}
