#include "domain.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Domain::Domain(int x, int y)
{
    QPointF position(x, y);
    pos = position;
    setFlag(ItemIsMovable);
    color = Qt::blue;
}

QRectF Domain::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 50, 50);
}

void Domain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect(pos.x(), pos.y(), 50, 50);
    QBrush brush(color);
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
QString Domain::getType() const
{
    return type;
}

void Domain::setType(const QString &value)
{
    type = value;
}
QString Domain::getName() const
{
    return name;
}

void Domain::setName(const QString &value)
{
    name = value;
}
QString Domain::getDescription() const
{
    return description;
}

void Domain::setDescription(const QString &value)
{
    description = value;
}
QColor Domain::getColor() const
{
    return color;
}

void Domain::setColor(const QColor &value)
{
    color = value;
}




