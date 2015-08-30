#include<cstdio>
#include<vector>
#include<random>
#include<cstdint>
#include<climits>
#include<cmath>
#include<cassert>
#include<algorithm>

using std::vector;
std::mt19937_64 engine(0);
std::uniform_int_distribution<long> distr(0, INT_MAX);

int max_bit(long data[], int n);
void radix_sort(long data[], int n);
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
    puts("UNSORTED:");
    for (int i = 0; i < ele_num; ++i)
        printf("vec[%d] = %ld\n", i, vec[i]);
    puts("------------------------");


    radix_sort(vec, ele_num);
    puts("SORTED:");
    for (int i = 0; i < ele_num; ++i)
        printf("vec[%d] = %ld\n", i, vec[i]);

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
        // assert(counter[9] == d);

        for (int j = n - 1; j >= 0; --j)
        {
            int k = (data[j] / radix) % 10;
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
