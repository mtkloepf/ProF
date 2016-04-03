#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "requirement.h"

Requirement::Requirement(float x, float y)
    : pos(QPointF(x, y))
{
    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
    defaultColor = Qt::magenta;
}

Requirement::~Requirement() {}

QRectF Requirement::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 75, 50);
}

void Requirement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2, Qt::DashLine));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(pos.x()+5, pos.y()+5, 70, 45);
}

QColor Requirement::getColor() const
{
    return color;
}

void Requirement::setColor(const QColor &value)
{
    color = value;
}

QColor Requirement::getDefaultColor() const
{
    return defaultColor;
}

void Requirement::setDefaultColor(const QColor &value)
{
    defaultColor = value;
}

void Requirement::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    //Create a new context menu to hold edit and delete actions
    //Then connect the signals to slot functions for the menu actions
    QMenu menu;
    QAction *editAction = menu.addAction("Edit");
    //connect(editAction, SIGNAL(triggered()), this, SLOT(editDomain()));
    QAction *deleteAction = menu.addAction("Delete");
    //connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteDomain()));

    menu.exec(event->screenPos());

}

void Requirement::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor.darker(125));
    update();
}

void Requirement::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor);
    update();
}

QString Requirement::getType() const
{
    return type;
}

void Requirement::setType(const QString &value)
{
    type = value;

    if(value == "Requirement") {
        setColor(Qt::magenta);
        setDefaultColor(Qt::magenta);
    }
    else {
        setColor("#8B008B");
        setDefaultColor("#8B008B");
    }
}
