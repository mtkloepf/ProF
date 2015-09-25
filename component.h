#ifndef COMPONENT_H
#define COMPONENT_H
#include <QString>
#include <stdlib.h>


class Component
{
public:
    Component();
    ~Component();
    QString name;
    QString description;

    QString getName();
    void setName(QString name);

    QString toString();

    QString getDescription();
    void setDescription(QString desc);

};

#endif // COMPONENT_H
