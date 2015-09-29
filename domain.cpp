#include "domain.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Domain::Domain(int x, int y)
{
    QPointF position(x, y);
    pos = position;
    setFlag(ItemIsMovable);
}

QRectF Domain::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 50, 50);
}

void Domain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect(pos.x(), pos.y(), 50, 50);
    QBrush brush(Qt::blue);
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

void Domain::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    event->accept();
}

Domain::~Domain()
{

}
