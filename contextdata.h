#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

/*******************************************************************************
/*! \class contextdata.h
 *
 *  This class holds the data required for the context and problem diagrams.
 *  This includes the entire list of objects that exist.
*******************************************************************************/
#include "interface.h"
#include "machinedomain.h"

class ContextData
{
public:
    ContextData(MachineDomain *machineDom);
    ~ContextData();

    QList<Domain *> & getDomains();

    bool addDomain(Domain &dom);
    void removeDomain(Domain &dom);

    bool addInterface(Interface &interface);
    void removeInterface(Interface &interface);

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
