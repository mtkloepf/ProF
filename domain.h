#ifndef DOMAIN_H
#define DOMAIN_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>
#include <QList>
#include "phenomenon.h"

class Domain : public QGraphicsItem
{
public:
    Domain(int x, int y);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    ~Domain();

    QString getType() const;
    void setType(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    QPointF pos;
    QList<Phenomenon> phenomena;
    QString type;
    QString name;
    QString description;
    QColor color;
};

#endif // DOMAIN_H
