#ifndef TARGETREPOSITORY_H
#define TARGETREPOSITORY_H

#include <QObject>
#include <QMap>

#include "target.h"

class Target;
class TargetRepository : public QObject
{
    Q_OBJECT
public:
    static TargetRepository& instance();

private:
    Q_DISABLE_COPY(TargetRepository)
    TargetRepository() = default;

private:
    QMap<int, Target> targets;
};

#endif  // TARGETREPOSITORY_H
