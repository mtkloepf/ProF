#include "problemdata.h"

ProblemData::ProblemData()
{

}

QList<Requirement *> ProblemData::getRequirements() const
{
    return requirements;
}

void ProblemData::setRequirements(const QList<Requirement *> &value)
{
    requirements = value;
}

void ProblemData::addRequirement(Requirement &value)
{
    if(!requirements.contains(&value))
        requirements.append(&value);
}

void ProblemData::removeRequirement(Requirement &value)
{
    if(requirements.contains(&value))
        requirements.removeOne(&value);
}

void ProblemData::clearRequirements()
{
    requirements.clear();
}
