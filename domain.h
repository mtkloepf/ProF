#ifndef DOMAIN_H
#define DOMAIN_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>
#include <QList>
#include <QMenu>
#include <QContextMenuEvent>
#include "phenomenon.h"
#include "editdomain.h"

class Domain : public QGraphicsObject
{
    Q_OBJECT
public:
    Domain(int x, int y);

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

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
    EditDomain *edit;
};

#endif // DOMAIN_H
