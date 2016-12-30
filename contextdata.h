#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

/*******************************************************************************
/*! \class contextdata.h
 *
 *  This class holds the data required for the context and problem diagrams.
 *  This includes the entire list of domains that exist.
*******************************************************************************/
#include <qlist.h>

#include "interface.h"
#include "machinedomain.h"

class ContextData : public QObject
{
    Q_OBJECT
public:
    ContextData(MachineDomain *machineDom);
    ~ContextData();

    QList<Domain *> & getDomains();
    void setDomains(const QList<Domain *> &value);

    void addDomain(Domain &dom);
    void removeDomain(Domain &dom);

    QStringList getDomainNames() const;
    Domain* findDomain(const QString name) const;

    int getDomainCount() const;

    QList<Interface *> getInterfaces() const;

//    void addLine(QPointF pos1, QPointF pos2);
//    QList<QLineF> getLines();

signals:
//    void lineAdded(QPointF pos1, QPointF pos2);

private:
//    QList<QLineF> lines;
    MachineDomain *machine;
    QList<Domain *> domains;
    QList<Interface *> interfaces;
    int domainCount;
};

#endif // CONTEXTDATA_H
