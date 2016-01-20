#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

/*******************************************************************************
/*! \class graphicsview.h
 *
 *  Custom graphics view
*******************************************************************************/
#include <QGraphicsView>
#include <QMouseEvent>

#include "domain.h"
#include "interface.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView( QGraphicsScene *graphicsScene, QWidget *parent=0);
    ~GraphicsView();

public slots:
    void mousePressEvent (QMouseEvent *event);
    void updateDomainNames(QString prev, QString current);

signals:
    void updateDomainList(QStringList);

public:
    QGraphicsScene *scene;

private:
    bool drawingLine;
    QPointF startPos;
    QPointF endPos;
    QLineF line;
    Domain *domain;
    Interface *interface;
    QStringList domains;
};

#endif // GRAPHICSVIEW_H
