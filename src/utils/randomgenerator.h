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
    double generateRandomDouble(double min, double max) const;
    QColor generateRandomColor() const;
    int generateRandomInt(int min, int max) const;
};

#endif  // RANDOMGENERATOR_H
