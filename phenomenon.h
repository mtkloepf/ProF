#ifndef PHENOMENON_H
#define PHENOMENON_H

/*******************************************************************************
/*! \class phenomenon.h
 *
 *  Storage for attributes of phenomena
*******************************************************************************/
#include <QStandardItem>
#include <QString>

class Phenomenon : public QStandardItem
{
public:
    Phenomenon(QString name, QString description);
    ~Phenomenon();

    bool operator==(const Phenomenon &phen);

public:
    QString name;
    QString description;
    QString type = "Event";

    Phenomenon* clone();
};

#endif // PHENOMENON_H
