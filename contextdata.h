#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

/*******************************************************************************
/*! \class contextdata.h
 *
 *  This class holds the data required for the context and problem diagrams.
 *  This includes the entire list of domains that exist.
*******************************************************************************/
#include <qlist.h>

#include "domain.h"

class ContextData
{
public:
    ContextData();
    ~ContextData();

    QList<Domain *> getDomains() const;
    void setDomains(const QList<Domain *> &value);

    void addDomain(Domain &dom);
    void removeDomain(Domain &dom);

    QStringList getDomainNames() const;
    Domain* findDomain(const QString name) const;

    int getDomainCount() const;

private:
    QList<Domain *> domains;
    int domainCount;
};

#endif // CONTEXTDATA_H
