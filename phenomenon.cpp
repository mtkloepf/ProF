#include "phenomenon.h"

Phenomenon::Phenomenon(QString Name, QString description)
    : name(Name), description(description)
{
    setFlags(flags() & ~Qt::ItemIsEditable);
}

Phenomenon::~Phenomenon()
{

}

bool Phenomenon::operator==(const Phenomenon &phen)
{
    return name == phen.name &&
            description == phen.description &&
            type == phen.type;
}

Phenomenon* Phenomenon::clone()
{
    return new Phenomenon(*this);
}

