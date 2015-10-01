#ifndef MACHINEDOMAIN_H
#define MACHINEDOMAIN_H

/*******************************************************************************
/*! \class machinedomain.h
 *
 *  Custom graphics object to act as the machine domain. Similar behavior to the
 *  domain class, but cannot be deleted, can only have on instance, and has
 *  limited editing options
*******************************************************************************/
#include <QGraphicsItem>
#include <QPainter>

class MachineDomain : public QGraphicsObject
{
public:
    MachineDomain();
    ~MachineDomain();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem
               *option, QWidget *widget);
};

#endif // MACHINEDOMAIN_H
