#ifndef PROBLEMDATA_H
#define PROBLEMDATA_H

#include <qlist.h>

#include "domain.h"
#include "requirement.h"

class ProblemData
{
public:
    ProblemData();

    QList<Requirement *> getRequirements() const;
    void setRequirements(const QList<Requirement *> &value);

    void addRequirement(Requirement &value);
    void removeRequirement(Requirement &value);

    void clearRequirements();

private:
    QList<Requirement *> requirements;
    QList<Domain *> activeDomains;
};

#endif // PROBLEMDATA_H
