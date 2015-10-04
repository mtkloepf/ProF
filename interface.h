#ifndef INTERFACE_H
#define INTERFACE_H

/*******************************************************************************
/*! \class interface.h
 *
 *  Header file for the interface class
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QPainter>

#include "editinterface.h"

class Interface : public QGraphicsObject
{
    Q_OBJECT

public:
    Interface(int x, int y);
    ~Interface();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private:
    QPointF pos;

    QString description;
    QString name;

    EditInterface *edit;
};

#endif // INTERFACE_H
