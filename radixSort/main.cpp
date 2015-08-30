#include<cstdio>
#include<vector>
#include<random>
#include<cstdint>
#include<climits>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<chrono>

using std::vector;
using namespace std::chrono;
std::mt19937_64 engine(std::random_device{}());
std::uniform_int_distribution<long> distr(0, INT_MAX);

int  max_bit        (long data[], int n);
void radix_sort     (long data[], int n);
void my_radix_sort  (long data[], int n);
bool sorted         (long data[], int n);
int main(int arg_num, char** args)
{
    if (arg_num < 2)
    {
        printf("usage: sort ele_num\n");
        return EXIT_FAILURE;
    }
    int ele_num = atoi(args[1]);
    printf("number of elements: %d\n", ele_num);

    long* vec = new long[ele_num];
    for (int i = 0; i < ele_num; ++i)
    {
        vec[i] = distr(engine);
    }
    // puts("UNSORTED:");
    // for (int i = 0; i < ele_num; ++i)
    //     printf("vec[%d] = %ld\n", i, vec[i]);
    // puts("------------------------");

    auto t1 = high_resolution_clock::now();
    my_radix_sort(vec, ele_num);
    auto t2 = high_resolution_clock::now();
    // puts("SORTED:");
    // for (int i = 0; i < ele_num; ++i)
    //     printf("vec[%d] = %ld\n", i, vec[i]);

    double timeSpan = duration_cast<duration<double>>(t2 - t1).count();
    printf("time spent: %g seconds\n", timeSpan);
    printf("sorted: %s\n", sorted(vec, ele_num) ? "yes" : "no");
    delete[] vec;
    return EXIT_SUCCESS;
}

void radix_sort(long data[], int n)
{
    int d = max_bit(data, n);

    long *tmp    = new long[n];
    int *counter = new int[10];

    for (int i = 1; i <= d; ++i)
    {
        int radix = pow(10, i - 1); // more readable, less effective than radix *= 10 in each loop
        std::fill(counter, counter + 10, 0);
        for (int j = 0; j < n; ++j)
        {
            int k = (data[j] / radix) % 10;
            counter[k]++;
        }
        // above loop 完成之后， counter 中是 data[i] 的 digit 的分布统计
        for (int j = 1; j < 10; ++j)
        {
            counter[j] += counter[j - 1];
        }

        for (int j = n - 1; j >= 0; --j)
        {
            int k               = (data[j] / radix) % 10;
            tmp[counter[k] - 1] = data[j];
            counter[k]--;
        }
        std::copy(tmp, tmp + n, data);
    }
    delete[] tmp;
    delete[] counter;
}
int max_bit(long data[], int n)
{
    long max_data = *(std::max_element(data + 0, data + n));

    int d = 1;
    long p = 10;

    while (max_data >= p)
    {
        p *=  10;
        ++d;
    }
    return d;
}
void my_radix_sort(long data[], int n)
{
    // my implementation, more readable, less efficient
    const int d = max_bit(data, n);
    for (int i = 0; i < d; ++i)
    {
        const int radix = pow(10, i);
        vector<long> tmp;
        vector<long> bucket[10];
        tmp.reserve(n);
        for(int j = 0; j < 10; ++j)
            bucket[j].reserve(n/10);
        for (int j = 0; j < n; ++j)
        {
            int k = (data[j] / radix) % 10;
            bucket[k].push_back(data[j]);
        }

        for (int j = 0; j < 10; ++j)
        {
            tmp.insert(tmp.end(), bucket[j].begin(), bucket[j].end());
        }
        std::copy(tmp.begin(), tmp.end(), data);
    }
}
bool sorted(long data[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        if (data[i] > data[i + 1])
            return false;
    }
    return true;
}
