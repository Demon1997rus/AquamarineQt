#include "target.h"

Target::Target() : Target(0, 0.0, 0.0) {}

Target::Target(int id, double distance, double peleng)
{
    this->id = id;
    this->distance = distance;
    this->peleng = peleng;
}

int Target::getId() const { return id; }

double Target::getDistance() const { return distance; }

void Target::setDistance(double value) { distance = value; }

double Target::getPeleng() const { return peleng; }

void Target::setPeleng(double value) { peleng = value; }
