#ifndef DOMAIN_H
#define DOMAIN_H

/*******************************************************************************
/*! \class domain.h
 *
 *  Header file for the domain class
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QLabel>
#include <QList>
#include <QPainter>

#include "editdomain.h"
#include "phenomenon.h"

class Domain : public QGraphicsObject
{
    Q_OBJECT
public:
    Domain(float x, float y);
    ~Domain();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QColor getColor() const;
    void setColor(const QColor &value);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

    QList<Phenomenon> getPhenomena() const;

    void addPhenomenon(const Phenomenon value);
    void removePhenomenon(const Phenomenon value);

public slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    void editDomain();
    void deleteDomain();

    void setPhenomena(const QList<Phenomenon> &value);

private slots:
    void updatePhenomena(QList<Phenomenon>);

private:
    QPointF pos;

    QString description;
    QString name;
    QString type;

    QColor color;
    QColor defaultColor;

    EditDomain *edit;

    QList<Phenomenon> phenomena;
};

#endif // DOMAIN_H
