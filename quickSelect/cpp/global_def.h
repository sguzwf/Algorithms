#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H
#include<random>
using namespace std;
#ifdef NDEBUG
default_random_engine g(std::random_device {}());
#else
default_random_engine g(0);
#endif
uniform_real_distribution<double> d(0, 1000);
#endif
