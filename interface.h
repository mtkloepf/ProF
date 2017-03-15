#ifndef INTERFACE_H
#define INTERFACE_H

/*******************************************************************************
/*! \class interface.h
 *
 *  Header file for the interface class
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <QList.h>
#include <QPainter>

#include "editinterface.h"

class Interface : public QGraphicsObject
{
    Q_OBJECT

public:
    Interface(int x, int y, QList<Domain *> &doms);
    ~Interface();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    int type() const;

    bool getEnabled();

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

    void updateDom1SharedPhenomena(QStringList phen);
    void updateDom2SharedPhenomena(QStringList phen);

    void disableInterface();

signals:
    void connectionCreated(Domain*, Domain*);

private:
    Domain *firstDomain;
    Domain *secondDomain;
    QPointF pos;
    QStringList dom1SharedPhenomena;
    QStringList dom2SharedPhenomena;
    QList<Domain *> &domains;

    bool enabled;

    QColor color;
    QColor defaultColor;

    QString description;
    QString name;

    EditInterface *edit;
};

#endif // INTERFACE_H
