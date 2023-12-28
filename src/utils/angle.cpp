#include "angle.h"

#include <cmath>

double Angle::normalizeAngle360(double x)
{
    x = fmod(x, 360.0);
    if (x < 0.0)
    {
        x += 360.0;
    }
    return x;
}

double Angle::normalizeAngle180(double x)
{
    x = fmod(x + 180.0, 360.0);
    if (x < 0.0)
    {
        x += 360.0;
    }
    return x - 180.0;
}
