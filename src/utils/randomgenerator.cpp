#include "randomgenerator.h"

#include <ctime>
#include <cstdlib>

RandomGenerator::RandomGenerator() { std::srand(static_cast<unsigned>(std::time(nullptr))); }

int RandomGenerator::generateRandomInt(int min, int max) const
{
    return min + std::rand() % (max - min + 1);
}

double RandomGenerator::generateRandomDouble(double min, double max) const
{
    return min + ((double)std::rand() / RAND_MAX) * (max - min);
}

QColor RandomGenerator::generateRandomColor() const
{
    return QColor::fromRgb(std::rand() % 256, std::rand() % 256, std::rand() % 256);
}
