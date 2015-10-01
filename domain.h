#ifndef DOMAIN_H
#define DOMAIN_H

/*******************************************************************************
/*! \class domain.h
 *
 *  Header file for the domain class
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QList>
#include <QPainter>
#include <QPoint>

#include "editdomain.h"

class Domain : public QGraphicsObject
{
    Q_OBJECT
public:
    Domain(int x, int y);
    ~Domain();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    QPointF pos;

    QString description;
    QString name;
    QString type;

    QColor color;

    EditDomain *edit;

    //QList<Phenomenon> phenomena;
};

#endif // DOMAIN_H
