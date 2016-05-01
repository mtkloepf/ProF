#ifndef MACHINEDOMAIN_H
#define MACHINEDOMAIN_H

/*******************************************************************************
/*! \class machinedomain.h
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QLabel>
#include <QList>
#include <QPainter>

#include "domain.h"

class MachineDomain : public QGraphicsObject
{
    Q_OBJECT

public:
    MachineDomain();
    ~MachineDomain();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem
               *option, QWidget *widget);

    QColor getColor() const;
    void setColor(const QColor &value);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

    int type() const;

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    QString getType() const;

    void editDomain();

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

private:
    QPointF pos;

    QString description;
    QString name;
    QString domainType;

    QColor color;
    QColor defaultColor;

    EditDomain *edit;
};

#endif // MACHINEDOMAIN_H
