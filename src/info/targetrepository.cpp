#include "targetrepository.h"

TargetRepository& TargetRepository::instance()
{
    static TargetRepository instance;
    return instance;
}

void TargetRepository::generateTarget()
{
    double distance = randomGenerator.generateRandomDouble(1., 200.);
    double heading = randomGenerator.generateRandomDouble(0., 360.);
    double bearing = randomGenerator.generateRandomDouble(0., 360.);
    QColor color = randomGenerator.generateRandomColor();
    Target target(distance, heading, bearing, color);
    targets.append(qMove(target));
    sortingByDistance();
    emit updateRepository();
}

void TargetRepository::updateTargets()
{
    for (Target& target : targets)
    {
        // Текущий угол направления
        double heading = target.getHeading();

        // Генерация случайного числа
        double newHeading = randomGenerator.generateRandomDouble(0., 360.);

        // Проверка на обратное направление ±45°
        // Если угол попадает в диапазон обратного направления, генерируем новый угол
        while ((newHeading > heading - 45 || qFuzzyCompare(newHeading, heading - 45)) &&
               (newHeading < heading + 45 || qFuzzyCompare(newHeading, heading + 45)))
        {
            newHeading = randomGenerator.generateRandomDouble(0., 360.);
        }
        target.updatePosition(newHeading, 20.);
    }
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

void TargetRepository::offFlashState()
{
    for (Target& target : targets)
    {
        target.setFlashState(false);
    }
    emit updateRepository();
}

Target* TargetRepository::findTargetById(int id)
{
    for (Target& target : targets)
    {
        if (target.getId() == id)
        {
            return &target;
        }
    }
    return nullptr;
}

void TargetRepository::sortingByDistance()
{
    qSort(targets.begin(), targets.end(), [](const Target& first, const Target& second) {
        return first.getDistance() < second.getDistance();
    });
}
