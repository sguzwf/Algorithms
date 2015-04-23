#ifndef POINT_H
#define POINT_H
#include<iostream>
class Point
{
    public:
        Point();
        Point(double,double,double);
        Point(const Point&);
        double x() const;
        double y() const;
        double z() const;
        Point& x(double);
        Point& y(double);
        Point& z(double);
        void printPoint() const;
    private:
        double _x,_y,_z;
};
#endif
