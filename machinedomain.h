#ifndef MACHINEDOMAIN_H
#define MACHINEDOMAIN_H

#include <QGraphicsItem>
#include <QPainter>

class MachineDomain : public QGraphicsItem
{
public:
    MachineDomain();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~MachineDomain();

};

#endif // MACHINEDOMAIN_H
