#include "targetrepository.h"

TargetRepository& TargetRepository::instance()
{
    static TargetRepository instance;
    return instance;
}

void TargetRepository::generateTarget()
{
    qDebug() << "Генерация цели";
    double distance = randomGenerator.generateRandomDouble(1., 200.);
    double heading = randomGenerator.generateRandomDouble(0., 360.);
    double bearing = randomGenerator.generateRandomDouble(0., 360.);
    QColor color = randomGenerator.generateRandomColor();
    Target target(distance, heading, bearing, color);
    qDebug() << target;
    targets.append(qMove(target));
    sortingByDistance();
    emit updateRepository();
}

const Target& TargetRepository::at(int index) const { return targets.at(index); }

void TargetRepository::clear()
{
    targets.clear();
    targets.squeeze();
    Target::resetCounter();
    emit updateRepository();
}

const QVector<Target>& TargetRepository::getTargets() const { return targets; }

int TargetRepository::size() const { return targets.size(); }

void TargetRepository::sortingByDistance()
{
    qSort(targets.begin(), targets.end(), [](const Target& first, const Target& second) {
        return first.getDistance() < second.getDistance();
    });
}
