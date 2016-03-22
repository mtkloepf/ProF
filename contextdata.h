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
#include "machinedomain.h"

class Interface;

class ContextData
{
public:
    ContextData(MachineDomain *machineDom);
    ~ContextData();

    QList<Domain *> getDomains() const;
    void setDomains(const QList<Domain *> &value);

    void addDomain(Domain &dom);
    void removeDomain(Domain &dom);

    QStringList getDomainNames() const;
    Domain* findDomain(const QString name) const;

    int getDomainCount() const;

    QList<Interface *> getInterfaces() const;

private:
    MachineDomain *machine;
    QList<Domain *> domains;
    QList<Interface *> interfaces;
    int domainCount;
};

#endif // CONTEXTDATA_H
