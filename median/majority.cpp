#include<iostream>
#include<stdio.h>
using namespace std;
int findMajorityElement(int* arr, int size);
int main()
{
    /* int arr[N] = {1,1,2,4,5,6,7,8,9}; */
    int arr[] = {2,2,2,3,4,5};
    int N = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < N; i++)
    {
        printf("arr[%d]=%d\n",i,arr[i]);
    }
    std::cout<<"========"<<std::endl;
    int m = findMajorityElement(arr,N);
    std::cout<<"med:"<<m<<std::endl;
    for(int i = 0; i < N; i++)
    {
        printf("arr[%d]=%d\n",i,arr[i]);
    }
    return 0;
}
int findMajorityElement(int* arr, int size) { 
    /* source from: http://stackoverflow.com/questions/4325200/find-majority-element-in-array */
    int count = 0, i;
    int majorityElement = 0;
    for (i = 0; i < size; i++) {
        if (count == 0)
            majorityElement = arr[i];
        if (arr[i] == majorityElement) 
            count++;
        else
            count--;
    }
    return majorityElement;
    /* count = 0; */
    /* for (i = 0; i < size; i++) */
    /*     if (arr[i] == majorityElement) */
    /*         count++; */
    /* if (count > size/2) */
    /*     return majorityElement; */
    /* return -1; */
}

