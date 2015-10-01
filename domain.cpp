#include "domain.h"
#include <QGraphicsSceneMouseEvent>
#include <QObject>

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

void Domain::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *editAction = menu.addAction("Edit");
    QAction *deleteAction = menu.addAction("Delete");

    if(menu.exec( event->screenPos() ) == deleteAction) {
        delete this;
    }
    else if(menu.exec( event->screenPos() ) == editAction) {
        edit = new EditDomain();
        edit->setDomainDescription(getDescription());
        edit->setDomainName(getName());
        edit->setDomainType(getType());
        connect(edit, SIGNAL(updateDescription(QString)), this, SLOT(setDescription(QString)));
        connect(edit, SIGNAL(updateName(QString)), this, SLOT(setName(QString)));
        connect(edit, SIGNAL(updateType(QString)), this, SLOT(setType(QString)));

        edit->show();
        edit->raise();
        edit->activateWindow();
    }
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




