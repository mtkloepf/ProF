/*******************************************************************************
/*! \class phenomenon.cpp
 *
 *  Implmentation for managing attributes and phenomenon data
*******************************************************************************/
#include "phenomenon.h"

/*******************************************************************************
/*! \brief Constructor for phenomena
 *
 * @param name        the name of the phenomenon
 * @param description the description of the phenomenon
*******************************************************************************/
Phenomenon::Phenomenon(QString Name, QString description)
    : name(Name), description(description)
{
    //Make sure the list of phenomena isn't editable itself
    setFlags(flags() & ~Qt::ItemIsEditable);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
Phenomenon::~Phenomenon()
{

}

/*******************************************************************************
/*! \brief Overloaded equality operator. Used to check equality between two
 *         phenomena
 *
 * @param phen the phenomenon to compare to
*******************************************************************************/
bool Phenomenon::operator==(const Phenomenon &phen)
{
    return name == phen.name &&
            description == phen.description &&
            type == phen.type;
}

/*******************************************************************************
/*! \brief Returns a clone of the current phenomenon
 *
 * @return see brief
*******************************************************************************/
Phenomenon* Phenomenon::clone()
{
    return new Phenomenon(*this);
}

QString Phenomenon::getName() const
{
    return name;
}

void Phenomenon::setName(QString newName)
{
    name = newName;
}

QString Phenomenon::getDescription() const
{
    return description;
}

void Phenomenon::setDescription(QString newDesc)
{
    description = newDesc;
}

QString Phenomenon::getType() const
{
    return type;
}

void Phenomenon::setType(QString newType)
{
    type = newType;
}

