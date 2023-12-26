#include "randomgenerator.h"

#include <ctime>
#include <cstdlib>

RandomGenerator::RandomGenerator() { std::srand(static_cast<unsigned>(std::time(nullptr))); }

double RandomGenerator::generateRandomDouble(double min, double max)
{
    return min + ((double)std::rand() / RAND_MAX) * (max - min);
}

QColor RandomGenerator::generateRandomColor()
{
    return QColor::fromRgb(std::rand() % 256, std::rand() % 256, std::rand() % 256);
}
