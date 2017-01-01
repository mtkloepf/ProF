/*******************************************************************************
/*! \class machinedomain.cpp
 *
 *  Custom graphics object to act as the machine domain. Similar behavior to the
 *  domain class, but cannot be deleted, can only have one instance, and has
 *  limited editing options. This class is very limited as a machine serves
 *  to act exclusively as a normal domain with some exceptions to its properties
*******************************************************************************/
#include "machinedomain.h"

/*******************************************************************************
/*! \brief Constructor
*******************************************************************************/
MachineDomain::MachineDomain()
    : Domain(0.0f, 0.0f)
{
    setFlag(ItemIsMovable);
    setDomainType("Machine");
    setName("Machine Domain");
    setGraphicsObjType(4);
    this->setAcceptedMouseButtons(!Qt::LeftButton); //Cannot move the machine
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
MachineDomain::~MachineDomain() {}
