#include "targetrepository.h"

TargetRepository& TargetRepository::instance()
{
    static TargetRepository instance;
    return instance;
}

/*!
 * \brief TargetRepository::generateTarget - генерация новой цели
 */
void TargetRepository::generateTarget()
{
    double initialDistance = randomGenerator.generateRandomDouble(0.0, 200.0);
    double initialBearing = randomGenerator.generateRandomDouble(0.0, 360.0);
    QColor initialColor = randomGenerator.generateRandomColor();
    Target newTarget(initialDistance, initialBearing, initialColor);
    targets.append(qMove(newTarget));
    sortingByDistance();
    emit updateRepository();
}

/*!
 * \brief TargetRepository::updateTargets - обновление целей
 */
void TargetRepository::updateTargets()
{
    if (targets.isEmpty())
        return;

    for (Target& target : targets)
    {
        double angleChange = randomGenerator.generateRandomDouble(-45.0, 45.0);
        target.updatePosition(20.0, angleChange);
    }
    sortingByDistance();
    emit updateRepository();
}

const Target& TargetRepository::at(int index) const { return targets.at(index); }

QVector<Target>::iterator TargetRepository::begin() { return targets.begin(); }

QVector<Target>::const_iterator TargetRepository::begin() const { return targets.begin(); }

QVector<Target>::iterator TargetRepository::end() { return targets.end(); }

QVector<Target>::const_iterator TargetRepository::end() const { return targets.end(); }

int TargetRepository::size() const { return targets.size(); }

void TargetRepository::sortingByDistance()
{
    qSort(targets.begin(), targets.end(), [](const Target& first, const Target& second) {
        return first.getDistance() < second.getDistance();
    });
}
