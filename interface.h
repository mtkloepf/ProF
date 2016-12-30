#ifndef INTERFACE_H
#define INTERFACE_H

/*******************************************************************************
/*! \class interface.h
 *
 *  Header file for the interface class
*******************************************************************************/
#include <QContextMenuEvent>
#include <QGraphicsItem>
#include <qlist.h>
#include <QPainter>

#include "domain.h"
#include "editinterface.h"

class Interface : public QGraphicsObject
{
    Q_OBJECT

public:
    Interface(int x, int y, QList<Domain *> &allDomains);
    ~Interface();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor getDefaultColor() const;
    void setDefaultColor(const QColor &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    Domain *getFirstDomain() const;
    Domain *getSecondDomain() const;

    void setFirstDomain(Domain *value);
    void setSecondDomain(Domain *value);

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

    void updateDom1SharedPhenomena(QList<Phenomenon> phen);
    void updateDom2SharedPhenomena(QList<Phenomenon> phen);

    void disableInterface();

private:
    Domain *firstDomain;
    Domain *secondDomain;
    QPointF pos;
    QList<Phenomenon> dom1SharedPhenomena;
    QList<Phenomenon> dom2SharedPhenomena;

    bool enabled;

    QColor color;
    QColor defaultColor;

    QString description;
    QString name;

    QList<Domain *> &domains;

    EditInterface *edit;
};

#endif // INTERFACE_H
