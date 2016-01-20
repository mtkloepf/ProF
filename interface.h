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

#include "domain.h"
#include "editinterface.h"
#include "phenomenon.h"

class Interface : public QGraphicsObject
{
    Q_OBJECT

public:
    Interface(int x, int y);
    ~Interface();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QColor getColor() const;
    void setColor(const QColor &value);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

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

    void updateDomains(QStringList value);

private:
    Domain *firstConn;
    Domain *secondConn;
    QStringList domains;
    QPointF pos;
    QList<Phenomenon> phenomena;

    QColor color;
    QColor defaultColor;

    QString description;
    QString name;

    EditInterface *edit;
};

#endif // INTERFACE_H
