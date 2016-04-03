#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QLabel>
#include <QList>
#include <QPainter>

class Requirement : public QGraphicsObject
{
    Q_OBJECT
public:
    Requirement(float x, float y);
    ~Requirement();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QColor getColor() const;
    void setColor(const QColor &value);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    QString getType() const;
    void setType(const QString &value);


private:
    QPointF pos;

    QString description;
    QString name;
    QString type;

    QColor color;
    QColor defaultColor;

    //EditRequirement *edit;

};

#endif // REQUIREMENT_H
