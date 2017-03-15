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
    Phenomenon* clone();

    QString getName() const;
    void setName(QString newName);

    QString getDescription() const;
    void setDescription(QString newDesc);

    QString getType() const;
    void setType(QString newType);

private:
    QString name;
    QString description;
    QString type = "Event";

};

#endif // PHENOMENON_H
