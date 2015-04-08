#ifndef NEIGHBOR_SEARCH_H
#define NEIGHBOR_SEARCH_H
#include<iostream>
#include<vector>
#include<map>
#include"Particle.h"
#include"SegmentTree.h"
using std::vector;
using std::map;
void neighborSearch(const vector<Particle*>&, map<Particle*,vector<Particle*>>&);
#endif
