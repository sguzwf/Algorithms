#include<vector>
#include<random>
#include"Event.h"
#include"Particle.h"
Event::Event(Particle& p,Event::EventType type)
    : _particle(&p), _type(type)
{}
bool Event::operator<(const Event& e)
{
    double xThis = _particle->x();
    double xThat = e.particle()->x();
    if(xThis < xThat)
        return true;
    else if(xThis > xThat)
        return false;
    else 
        return _type < e.type();
}
bool Event::operator>(const Event& e)
{
    double xThis = _particle->x();
    double xThat = e.particle()->x();
    if(xThis > xThat)
        return true;
    else if(xThis < xThat)
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
vector<Event> genEventVector(const vector<Particle>& pVec)
{
    vector<Event> eVec;
    eVec.reserve(pVec.size() * 3);
    for(auto p : pVec)
    {
        eVec.push_back(Event(p,Event::Start));
        eVec.push_back(Event(p,Event::Insert));
        eVec.push_back(Event(p,Event::Query));
    }
    return eVec;
}

template<typename T>
vector<T> quickSort(const vector<T>& eVec)
{
    // a simple quickSort, without much optimization
    // use random pivot
    std::default_random_engine g(std::random_device{}());
    std::uniform_int_distribution<size_t> distr(0,eVec.size()-1);
    auto pivot       = eVec[distr(g)];
    auto eVecLess    = vector<T>();
    auto eVecEqual   = vector<T>();
    auto eVecGreater = vector<T>();

    for(auto e :eVec)
    {
        if(e < pivot)
            eVecLess.push_back(e);
        else if(e > pivot)
            eVecGreater.push_back(e);
        else 
            eVecEqual.push_back(e);
    }
    auto sortedVec = vector<T>(quickSort(eVecLess));
    for(auto e : eVecEqual)
        sortedVec.push_back(e);
    for(auto e : quickSort(eVecGreater))
        sortedVec.push_back(e);
    return sortedVec;
}
