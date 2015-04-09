#ifndef NEIGHBOR_SEARCH_H
#define NEIGHBOR_SEARCH_H
#include<iostream>
#include<vector>
#include<map>
#include"Particle.h"
#include"SegmentTree.h"
#include"Event.h"
using std::vector;
using std::map;
void neighborSearch(
        const vector<Particle*>&,
        map<Particle*,vector<Particle*>>&,
        StaticSegmentTree&);
bool autoTestSearchResult(map<Particle*,vector<Particle*>>);
#endif
