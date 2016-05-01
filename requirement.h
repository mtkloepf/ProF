#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QLabel>
#include <QList>
#include <QPainter>

#include "editrequirement.h"

class Requirement : public QGraphicsObject
{
    Q_OBJECT
public:
    Requirement(float x, float y, ContextData *data);
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

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    void editRequirement();
    void deleteRequirement();

    QString getType() const;
    void setType(const QString &value);

    int type() const;

    void setDomains(const QString first, const QString second);

    void updateDom1SharedPhenomena(QList<Phenomenon> phen);
    void updateDom2SharedPhenomena(QList<Phenomenon> phen);

private:
    Domain *firstDomain;
    Domain *secondDomain;
    QPointF pos;
    QList<Phenomenon> dom1SharedPhenomena;
    QList<Phenomenon> dom2SharedPhenomena;

    ContextData *context;

    QString description;
    QString name;
    QString reqType;

    QColor color;
    QColor defaultColor;

    EditRequirement *edit;
};

#endif // REQUIREMENT_H
