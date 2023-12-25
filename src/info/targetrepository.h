#ifndef TARGETREPOSITORY_H
#define TARGETREPOSITORY_H

#include <QObject>
#include <QVector>

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
    void add(const Target& target);
    const Target& at(int index) const;
    int size() const;

private:
    void sortingByDistance();

private:
    Q_DISABLE_COPY(TargetRepository)
    TargetRepository() = default;

private:
    QVector<Target> targets;
};

#endif  // TARGETREPOSITORY_H
