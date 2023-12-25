#include "targetrepository.h"

#include <QDebug>

TargetRepository& TargetRepository::instance()
{
    static TargetRepository instance;
    return instance;
}

void TargetRepository::add(const Target& target)
{
    targets.push_back(target);
    sortingByDistance();
}

const Target& TargetRepository::at(int index) const { return targets.at(index); }

int TargetRepository::size() const { return targets.size(); }

void TargetRepository::sortingByDistance()
{
    qSort(targets.begin(), targets.end(), [](const Target& first, const Target& second) {
        return first.getDistance() < second.getDistance();
    });
}
