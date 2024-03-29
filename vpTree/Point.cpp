#include"Point.h"
#include<iostream>
#include<limits>
#include<cmath>
using std::cout;
using std::endl;
Point::Point()
    : _x(std::numeric_limits<double>::infinity()),
      _y(std::numeric_limits<double>::infinity()),
      _z(std::numeric_limits<double>::infinity())
{}
Point::Point(double x, double y, double z)
    : _x(x), _y(y), _z(z)
{}
Point::Point(const Point& p)
    : _x(p._x), _y(p._y), _z(p._z)
{}
double Point::x() const
{
    return _x;
}
double Point::y() const
{
    return _y;
}
double Point::z() const
{
    return _z;
}
Point& Point::x(double v)
{
    _x = v;
    return *this;
}
Point& Point::y(double v)
{
    _y = v;
    return *this;
}
Point& Point::z(double v)
{
    _z = v;
    return *this;
}
void Point::printPoint() const
{
    cout << "(" << _x << ", " << _y << ", " << _z << ")" << endl;
}
double Point::distance(const Point& p) const
{
    return sqrt(
               (_x - p._x) * (_x - p._x) +
               (_y - p._y) * (_y - p._y) +
               (_z - p._z) * (_z - p._z)
           );
}
bool Point::inRange(const Point& p, double radius) const
{
    return this->distance(p) < radius;
}
bool Point::operator==(const Point& p) const
{
    return (_x == p._x) && (_y == p._y) && (_z == p._z);
}
