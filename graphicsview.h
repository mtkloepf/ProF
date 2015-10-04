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
public:
    GraphicsView( QGraphicsScene *graphicsScene, QWidget *parent=0);
    ~GraphicsView();

public slots:
    void mousePressEvent (QMouseEvent *event);

public:
    QGraphicsScene *scene;

private:
    Domain *domain;
    Interface *interface;
};

#endif // GRAPHICSVIEW_H
