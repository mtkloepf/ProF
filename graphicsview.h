#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

/*******************************************************************************
/*! \class graphicsview.h
 *
 *  Custom graphics view
*******************************************************************************/
#include <QGraphicsView>
#include <QMouseEvent>

#include "contextdata.h"
#include "domain.h"
#include "editdomain.h"
#include "interface.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView( QGraphicsScene *graphicsScene, ContextData *data, QWidget *parent=0);
    ~GraphicsView();

public slots:
    void mousePressEvent (QMouseEvent *event);
    void deleteDomain(Domain *dom);

signals:
    void updateDomainList(QStringList);

public:
    QGraphicsScene *scene;

private:
    ContextData *context;

    bool drawingLine; //Unused
    QPointF startPos; //Unused
    QPointF endPos;   //Unused
    QLineF line;      //Unused

    Domain *domain;
    Interface *interface;

    QStringList domainNames;
    QList<Domain *> domains;

    EditDomain *editDom;
};

#endif // GRAPHICSVIEW_H
