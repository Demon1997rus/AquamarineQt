#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <QColor>

/*!
 * \brief The RandomGenerator class - утилита для генерирования рандомных значений
 */
class RandomGenerator
{
public:
    RandomGenerator();

public:
    double generateRandomDouble(double min, double max);
    QColor generateRandomColor();
};

#endif  // RANDOMGENERATOR_H
