#include "targetrepository.h"

TargetRepository& TargetRepository::instance()
{
    static TargetRepository instance;
    return instance;
}
