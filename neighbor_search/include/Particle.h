#ifndef PARTICLE_H
#define PARTICLE_H
#include<vector>
using std::vector;
class Particle
{
private:
    // the whole search range would be rectangular formed by:
    // (x-rx,y-ry),(x-rx,y+ry),(x+rx,y-ry),(x+rx,y+ry)
    // a particle is immutable
    const double _x  = 0;  // position x
    const double _y  = 0;  // position y
    const double _rx = 0;  // searchRange x
    const double _ry = 0;  // searchRange y
public:
    Particle();
    Particle(double, double, double, double);
    double x()  const;
    double y()  const;
    double rx() const;
    double ry() const;
    double distance(const Particle&) const;
    bool inRange(const Particle&) const;
    void printInfo();
};
void genRandPartiles(double, double , double , unsigned int , vector<Particle*>& );
#endif
