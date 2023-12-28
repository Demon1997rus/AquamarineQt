#ifndef ANGLE_H
#define ANGLE_H

/*!
 * \brief The Angle class - утилита для работы с углами
 */
class Angle
{
public:
    // Диапазон (0, 360)
    static double normalizeAngle360(double x);

    // Диапазон (-180, +180)
    static double normalizeAngle180(double x);
};

#endif  // ANGLE_H
