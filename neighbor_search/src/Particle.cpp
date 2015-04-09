#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#include<cmath>
#include<limits>
#include<random>
#include"Particle.h"
using std::vector;
using std::map;
Particle::Particle()
    : _x(0),
      _y(0),
      _rx(std::numeric_limits<double>::infinity()),
      _ry(std::numeric_limits<double>::infinity())
{}
Particle::Particle(double x, double y, double rx, double ry)
    : _x(x), _y(y), _rx(rx), _ry(ry)
{
    assert(rx > 0);
    assert(ry > 0);
}
double Particle::x() const
{
    return _x;
}
double Particle::y() const
{
    return _y;
}
double Particle::rx() const
{
    return _rx;
}
double Particle::ry() const
{
    return _ry;
}
double Particle::distance(const Particle& p) const
{
    auto dx = _x - p._x;
    auto dy = _y - p._y;
    return sqrt(dx * dx + dy * dy);
}
bool Particle::inRange(const Particle& p) const
{
    // p is in range of **this**
    bool xInRange = (_x - _rx <= p._x) &&  (p._x <= _x + _rx);
    bool yInRange = (_y - _ry <= p._y) &&  (p._y <= _y + _ry);
    return xInRange && yInRange;
}
void Particle::printInfo()
{
    std::cout << "Particle Info" << std::endl;
    std::cout << "x: "  << _x  << std::endl;
    std::cout << "y: "  << _y  << std::endl;
    std::cout << "rx: " << _rx << std::endl;
    std::cout << "ry: " << _ry << std::endl;
    std::cout << "__________________________________" << std::endl;
}
void genRandPartiles(double leftRange, double rightRange, double maxR, unsigned int particleNum, vector<Particle*>& vec) {
    // 随机生成一些粒子
    assert(vec.empty());
    assert(maxR > 0);
    std::default_random_engine gen(0);
    std::uniform_real_distribution<double>distrPos(leftRange, rightRange);
    std::uniform_real_distribution<double>distR(0, maxR);
    for (unsigned int i = 0; i < particleNum; i++)
    {
        double randX  = distrPos(gen);
        double randY  = distrPos(gen);
        double randRx = distR(gen);
        double randRy = distR(gen);
        vec.push_back(new Particle(randX, randY, randRx, randRy));
    }
}
