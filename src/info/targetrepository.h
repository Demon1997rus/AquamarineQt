#ifndef TARGETREPOSITORY_H
#define TARGETREPOSITORY_H

#include <QObject>
#include <QVector>

#include "utils/randomgenerator.h"
#include "target.h"

/*!
 * \brief The TargetRepository class - репозиторий с целями
 */
class TargetRepository : public QObject
{
    Q_OBJECT
public:
    static TargetRepository& instance();  // Singleton

public:
    const Target& at(int index) const;
    void generateTarget();
    void updateTargets();
    int size() const;

signals:
    void updateRepository();

private:
    void sortingByDistance();

private:
    Q_DISABLE_COPY(TargetRepository)
    TargetRepository() = default;

private:
    QVector<Target> targets;
    RandomGenerator randomGenerator;
};

#endif  // TARGETREPOSITORY_H
