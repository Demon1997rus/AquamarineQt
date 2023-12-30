#include "target.h"

#include <QtMath>
#include "utils/angle.h"

unsigned long long int Target::ID = 0;

Target::Target(double _distance, double _heading, double _bearing, const QColor& _color)
  : distance(_distance), heading(_heading), bearing(_bearing), color(_color)
{
    id = ++ID;
    position.setX(qCos(qDegreesToRadians(bearing)) * distance);
    position.setY(qSin(qDegreesToRadians(bearing)) * distance);
    history.enqueue(position);
}

Target::Target(const Target& other) { *this = other; }

Target::Target(Target&& other) Q_DECL_NOTHROW { *this = qMove(other); }

Target& Target::operator=(const Target& other)
{
    id = other.id;
    distance = other.distance;
    heading = other.heading;
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
    heading = other.heading;
    bearing = other.bearing;
    color = qMove(other.color);
    position = other.position;
    history = qMove(other.history);
    return *this;
}

int Target::getId() const { return id; }

double Target::getDistance() const { return distance; }

double Target::getHeading() const { return heading; }

double Target::getBearing() const { return bearing; }

const QColor& Target::getColor() const { return color; }

const QPointF& Target::getPosition() const { return position; }

const QQueue<QPointF>& Target::getHistory() const { return history; }

void Target::resetCounter() { ID = 0; }

void Target::updatePosition(double newHeading, double length)
{
    double dx = qCos(qDegreesToRadians(newHeading)) * length;  // Вычисление смещения по x
    double dy = qSin(qDegreesToRadians(newHeading)) * length;  // Вычисление смещения по y
    position.rx() += dx;   // обновление координаты x
    position.ry() += dy;   // Обновление координаты y
    heading = newHeading;  // Обновление угла направления движения

    // Вычисляем новую дистанцию по теореме пифагора
    distance = qSqrt(qPow(position.x(), 2) + qPow(position.y(), 2));

    // Вычисляем новый пеленг относительно центра круга, используя арктангенс,
    // чтобы найти угол между вектором от центра круга до цели и осью x.
    // Обязательно нужно перевести из радианов в градусы и нормализовать его в диапазон от 0 до 360
    // так как результат мы получим от - 180 до 180
    bearing = Angle::normalizeAngle360(qRadiansToDegrees(qAtan2(position.y(), position.x())));

    // После обновления позиций добавляем её в историю перемещения цели
    history.enqueue(position);

    // Так как хранить нам надо 3 последних позиций + текущую(итого 4)
    // если элементов больше 4 в очереди то удаляем последнию позицию
    if (history.size() > 4)
    {
        history.dequeue();
    }
}

QDebug operator<<(QDebug debug, const Target& other)
{
    QDebugStateSaver saver(debug);
    Q_UNUSED(saver)
    debug << "Идентификатор:" << other.id;
    debug << "Дистанция:" << other.distance;
    debug << "Курс:" << other.heading;
    debug << "Пеленг:" << other.bearing;
    debug << "Цвет:" << other.color;
    debug << "Текущая позиция:" << other.position;
    debug << "История перемещения:" << other.history;
    return debug;
}
