#include<iostream>
#include<vector>
#include<random>
#include"Event.h"
#include"Particle.h"
Event::Event(Particle* p, Event::EventType type)
    : _particle(p), _type(type)
{}
bool Event::operator<(const Event& e)
{
    double xThis = _particle->x();
    double xThat = e.particle()->x();
    if (xThis < xThat)
        return true;
    else if (xThis > xThat)
        return false;
    else
        return _type < e.type();
}
bool Event::operator>(const Event& e)
{
    double xThis = _particle->x();
    double xThat = e.particle()->x();
    if (xThis > xThat)
        return true;
    else if (xThis < xThat)
        return false;
    else
        return _type > e.type();
}
Particle* Event::particle() const
{
    return _particle;
}
Event::EventType Event::type() const
{
    return _type;
}
vector<Event> genEventVector(const vector<Particle*>& pVec)
{
    vector<Event> eVec;
    eVec.reserve(pVec.size() * 3);
    for (auto p : pVec)
    {
        eVec.push_back(Event(p, Event::Start));
        eVec.push_back(Event(p, Event::Insert));
        eVec.push_back(Event(p, Event::Query));
    }
    return eVec;
}

// vector<Event> quickSort(const vector<Event>&);
vector<Event> quickSort(const vector<Event>& eVec)
{
    // a simple quickSort, without much optimization
    // use random pivot
    if (eVec.empty())
        return eVec;
    std::default_random_engine g(std::random_device {}());
    std::uniform_int_distribution<size_t> distr(0, eVec.size() - 1);
    auto index       = distr(g);
    auto pivot       = eVec[index];
    auto eVecLess    = vector<Event>();
    auto eVecEqual   = vector<Event>();
    auto eVecGreater = vector<Event>();

    for (auto e : eVec)
    {
        if (e < pivot)
            eVecLess.push_back(e);
        else if (e > pivot)
            eVecGreater.push_back(e);
        else
            eVecEqual.push_back(e);
    }
    auto sortedVec = vector<Event>(quickSort(eVecLess));
    for (auto e : eVecEqual)
        sortedVec.push_back(e);
    for (auto e : quickSort(eVecGreater))
        sortedVec.push_back(e);
    return sortedVec;
}
void Event::printEventInfo()
{
    switch (_type)
    {
    case Event::Start:
        std::cout << "type: Start" << std::endl;
        break;
    case Event::Insert:
        std::cout << "type: Insert" << std::endl;
        break;
    case Event::Query:
        std::cout << "type: Query" << std::endl;
        break;
    }
    std::cout << "Particle Info" << std::endl;
    _particle->printInfo();
}
bool autoEventTest(const vector<Particle*>& pVec)
{
    auto eVec   = genEventVector(pVec);
    if (eVec.size() != pVec.size() * 3)
        return false;
    auto eVecSorted = quickSort(eVec);
    for (unsigned long i = 0; i < eVecSorted.size() - 1; i++)
    {
        if (eVecSorted[i] > eVecSorted[i + 1]) // 因为没有重载等于号，所以用“不大于”来表示小于等于
        {
            std::cout << "test failer in quickSort test:" << std::endl;
            std::cout << "i = " << i << std::endl;
            std::cout << "event[i]" << std::endl;
            eVecSorted[i].printEventInfo();
            std::cout << "event[i+1]" << std::endl;
            eVecSorted[i + 1].printEventInfo();
            return false;
        }
    }
    std::cout << "Event Test Passed!" << std::endl;
    return true;
}
