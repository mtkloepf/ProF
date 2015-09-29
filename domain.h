#ifndef DOMAIN_H
#define DOMAIN_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>

class Domain : public QGraphicsItem
{
public:
    Domain(int x, int y);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~Domain();

private:
    QPointF pos;
};

#endif // DOMAIN_H
