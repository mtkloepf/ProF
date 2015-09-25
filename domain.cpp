#include "domain.h"

Domain::Domain(QPointF position)
    : pos(position)
{
    setFlag(ItemIsMovable);
}

QRectF Domain::boundingRect() const
{
    return QRectF(0, 0, 50, 30);
}

void Domain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect(pos.x(), pos.y(), 50, 30);
    QBrush brush(Qt::blue);
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
    update();
}

Domain::~Domain()
{

}
