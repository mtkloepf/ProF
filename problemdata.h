#ifndef PROBLEMDATA_H
#define PROBLEMDATA_H

#include <qlist.h>

#include "requirement.h"

class ProblemData
{
public:
    ProblemData();

    QList<Requirement *> getRequirements() const;
    void setRequirements(const QList<Requirement *> &value);

    void addRequirement(Requirement &value);
    void removeRequirement(Requirement &value);

private:
    QList<Requirement *> requirements;
};

#endif // PROBLEMDATA_H
