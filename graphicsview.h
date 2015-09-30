#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include "domain.h"
#include <QGraphicsSceneContextMenuEvent>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView( QGraphicsScene *graphicsScene, QWidget *parent=0);
    ~GraphicsView();
    QGraphicsScene *m_scene;

public slots:
    void mousePressEvent (QMouseEvent *event);

protected:


private:
    Domain *domain;
};

#endif // GRAPHICSVIEW_H
