#include "target.h"

Target::Target() : Target(0.0, 0.0) {}

Target::Target(double distance, double peleng)
{
    this->id = ++ID;
    this->distance = distance;
    this->peleng = peleng;
}

Target::Target(const Target& other) { *this = other; }

Target& Target::operator=(const Target& other)
{
    id = other.id;
    distance = other.distance;
    peleng = other.peleng;
}

int Target::getId() const { return id; }

double Target::getDistance() const { return distance; }

void Target::setDistance(double value) { distance = value; }

double Target::getPeleng() const { return peleng; }

void Target::setPeleng(double value) { peleng = value; }

int Target::ID = 0;
