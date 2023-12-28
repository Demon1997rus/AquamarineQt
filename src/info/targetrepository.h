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
    void generateTarget();

public:
    const Target& at(int index) const;
    void clear();
    const QVector<Target>& getTargets() const;
    int size() const;

signals:
    void updateRepository();

private:
    void sortingByDistance();

private:
    TargetRepository() = default;
    Q_DISABLE_COPY(TargetRepository)
    QVector<Target> targets;
    RandomGenerator randomGenerator;
};

#endif  // TARGETREPOSITORY_H
