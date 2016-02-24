#ifndef INTERFACE_H
#define INTERFACE_H

/*******************************************************************************
/*! \class interface.h
 *
 *  Header file for the interface class
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QPainter>

#include "contextdata.h"
#include "editinterface.h"

class Interface : public QGraphicsObject
{
    Q_OBJECT

public:
    Interface(int x, int y, ContextData *data);
    ~Interface();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

    QColor getColor() const;
    void setColor(const QColor &value);

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    void editInterface();
    void deleteInterface();

    void setDomains(const QString first, const QString second);

private:
    Domain *firstDomain;
    Domain *secondDomain;
    QPointF pos;
    QList<Phenomenon> phenomena;

    QColor color;
    QColor defaultColor;

    QString description;
    QString name;

    ContextData *context;

    EditInterface *edit;
};

#endif // INTERFACE_H
