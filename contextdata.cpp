/*******************************************************************************
/*! \class contextdata.cpp
 *
 * Implementation of the contextdata class
*******************************************************************************/
#include "contextdata.h"

#include <qdebug.h>

ContextData::ContextData(MachineDomain *machineDom)
    : domainCount(0),
      machine(machineDom)
{

}

ContextData::~ContextData()
{
    delete machine;
}

/*******************************************************************************
/*! \brief Retrieval for pointers to all domains
 *
 * @return a list of pointers to all the domains that exist in the frame
*******************************************************************************/
QList<Domain *> & ContextData::getDomains()
{
    return domains;
}

/*******************************************************************************
/*! \brief Setter for list of pointers to all domains
 *
 * @param value a list of pointers to all the domains that exist in the frame
*******************************************************************************/
void ContextData::setDomains(const QList<Domain *> &value)
{
    domains = value;
}

/*******************************************************************************
/*! \brief Add a domain to the context
 *
 * @param dom domain to be added if it does not already exist in the context
*******************************************************************************/
void ContextData::addDomain(Domain &dom)
{
    if(!domains.contains(&dom)) {
        domains.append(&dom);
        domainCount++;
    }
}

/*******************************************************************************
/*! \brief Remove a domain from the context
 *
 * @param dom domain to be removed if it exists in the context
*******************************************************************************/
void ContextData::removeDomain(Domain &dom)
{
    if(domains.contains(&dom)) {
        domains.removeOne(&dom);
        domainCount--;
    }
}

/*******************************************************************************
/*! \brief Retrieval function to get a list of all domain names in string format
 *
 * @return a string list containing the name of all the domains that exist
*******************************************************************************/
QStringList ContextData::getDomainNames() const
{
    QStringList names;
    for(int i = 0; i < domains.size(); i++) {
        if(domains.at(i) && domains.at(i)->getEnabled())
            names.append(domains.at(i)->getName());
    }
    return names;
}

/*******************************************************************************
/*! \brief Retrieval function for a specific domain
 *
 * @return a pointer to a domain found based on the name passed in
*******************************************************************************/
Domain* ContextData::findDomain(const QString name) const
{
    foreach(Domain *dom, domains) {
        if(dom->getName() == name) {
            return dom;
        }
    }
    return NULL;
}

/*******************************************************************************
/*! \brief Get the number of domains in the context
 *
 *  Used to add default names to domains when added
*******************************************************************************/
int ContextData::getDomainCount() const
{
    return domainCount;
}

QList<Interface *> ContextData::getInterfaces() const
{
    return interfaces;
}

//void ContextData::addLine(QLineF *line)
//{
//    qDebug() << "Line added";
//    lines.append(*line);
//    emit lineAdded(line->p1(), line->p2());
//}

//QList<QLineF> ContextData::getLines()
//{
//    return lines;
//}
