#include "machinedomain.h"

MachineDomain::MachineDomain()
{
    setFlag(ItemIsMovable);
}

QRectF MachineDomain::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void MachineDomain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

MachineDomain::~MachineDomain()
{

}
