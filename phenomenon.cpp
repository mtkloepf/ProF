#include "phenomenon.h"

Phenomenon::Phenomenon(QString Name, QString description)
    : name(Name), description(description)
{
    setFlags(flags() & ~Qt::ItemIsEditable);
}

Phenomenon::~Phenomenon()
{

}

Phenomenon* Phenomenon::clone()
{
    return new Phenomenon(*this);
}

