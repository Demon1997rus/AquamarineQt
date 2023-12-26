#include "target.h"

#include <QtMath>

Target::Target() : Target(0.0, 0.0, QColor()) {}

Target::Target(double _distance, double _bearing, const QColor& _color)
  : distance(_distance), bearing(_bearing), color(_color)
{
    this->id = ++ID;
    position.setX(distance * qCos(qDegreesToRadians(bearing)));
    position.setY(distance * qSin(qDegreesToRadians(bearing)));
    history.append(position);
}

Target::Target(const Target& other) { *this = other; }

Target::Target(Target&& other) Q_DECL_NOTHROW { *this = qMove(other); }

Target& Target::operator=(const Target& other)
{
    id = other.id;
    distance = other.distance;
    bearing = other.bearing;
    color = other.color;
    position = other.position;
    history = other.history;
    return *this;
}

Target& Target::operator=(Target&& other) Q_DECL_NOTHROW
{
    id = other.id;
    distance = other.distance;
    bearing = other.bearing;
    color = qMove(other.color);
    position = other.position;
    history = qMove(other.history);
    return *this;
}

int Target::getId() const { return id; }

double Target::getDistance() const { return distance; }

double Target::getBearing() const { return bearing; }

void Target::updatePosition(double distanceChange, double angleChange)
{
    // Обновляем угол
    bearing += angleChange;

    // Нормализуем если вышел за пределы 360 градусов
    bearing = fmod(bearing, 360.0);
    if (bearing < 0)
    {
        bearing += 360.0;
    }

    // Обновляем дистанцию
    distance += distanceChange;

    // Гарантия того, что дистанция не будет отрицательной
    distance = qMax(distance, 0.0);

    // Обновляем позицию цели
    position.setX(distance * qCos(qDegreesToRadians(bearing)));
    position.setY(distance * qSin(qDegreesToRadians(bearing)));

    // Добавляем новую позицию в историю
    history.prepend(position);

    // Ограничиваем количество точек до 3 последних положений цели
    if (history.size() > 3)
    {
        history.removeLast();
    }
}

int Target::ID = 0;
