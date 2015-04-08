#ifndef EVENT_H
#define EVENT_H
#include<vector>
#include"Particle.h"
using std::vector;
class Event
{
public:
    enum EventType
    {
        Start = 0,
        Insert,
        Query
    };
    Event(Particle&, EventType);
    bool operator<(const Event&);       // 事件要排序
    bool operator>(const Event&);       // 事件要排序
    // 不定义等于号，因为等于是反直觉的，即大于和小于都是相对于particle的x坐标以及event类型来定
    // 然而如果定义等于，则直觉上，应该也是两个相同的particle
    // 因而，event的大小关系只有大于，小于，既不大于也不小于。
    Particle* particle() const;   // 当遇到insert事件时，要把粒子插入
    EventType type() const;             // 判断事件类型，决定是否排序
private:
    Particle* _particle;          
    EventType _type;                    // judge whether to insert
};
vector<Event> genEventVector(const vector<Particle>&);  // 由粒子数组生成事件序列，未排序
vector<Event> quickSort(const vector<Event>&);          // 对未排序的事件序列进行排序。
#endif
