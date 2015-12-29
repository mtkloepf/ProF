#include "phenomenon.h"

Phenomenon::Phenomenon(QString name, QString description)
{
    this->name = name;
    this->description = description;
}

Phenomenon::~Phenomenon()
{
    setFlags(flags() & ~Qt::ItemIsEditable);
}

Phenomenon* Phenomenon::clone()
{
    return new Phenomenon(*this);
}

