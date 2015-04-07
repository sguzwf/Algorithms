#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#include"Particle.h"
using std::vector;
using std::map;
Particle::Particle()
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
Particle& Particle::x(double xx)
{
    _x = xx;
    return *this;
}
Particle& Particle::y(double yy)
{
    _y = yy;
    return *this;
}
Particle& Particle::rx(double rrxx)
{
    assert(rrxx > 0);
    _rx = rrxx;
    return *this;
}
Particle& Particle::ry(double rryy)
{
    assert(rryy > 0);
    _ry = rryy;
    return *this;
}
Particle& Particle::operator=(const Particle& p)
{
    _x  = p._x;
    _y  = p._y;
    _rx = p._rx;
    _ry = p._ry;
    return *this;
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
