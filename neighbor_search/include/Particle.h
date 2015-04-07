#ifndef PARTICLE_H
#define PARTICLE_H
class Particle
{
private:
    // the whole search range would be rectangular formed by:
    // (x-rx,y-ry),(x-rx,y+ry),(x+rx,y-ry),(x+rx,y+ry)
    double _x  = 0;  // position x
    double _y  = 0;  // position y
    double _rx = 0;  // searchRange x
    double _ry = 0;  // searchRange y
public:
    Particle();
    Particle(double, double, double, double);
    double x()  const;
    double y()  const;
    double rx() const;
    double ry() const;
    Particle& x(double);
    Particle& y(double);
    Particle& rx(double);
    Particle& ry(double);
    Particle& operator=(const Particle&);
    void printInfo();
};
#endif
