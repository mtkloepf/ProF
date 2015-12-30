#ifndef PHENOMENON_H
#define PHENOMENON_H

#include <QStandardItem>
#include <QString>

class Phenomenon : public QStandardItem
{
public:
    Phenomenon(QString name, QString description);
    ~Phenomenon();

    QString name;
    QString description;
    QString type = "Event";

    Phenomenon* clone();
};

#endif // PHENOMENON_H
