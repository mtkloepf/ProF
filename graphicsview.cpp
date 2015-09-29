#include "graphicsview.h"
#include "domain.h"
#include <QDebug>

GraphicsView::GraphicsView( QGraphicsScene *graphicsScene, QWidget *parent)
    : QGraphicsView( graphicsScene, parent),
      m_scene(graphicsScene)
{
    setScene(m_scene);
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::mousePressEvent( QMouseEvent *event)
{
    QPointF pos = mapToScene( event->pos() );
    if(event->button() == Qt::LeftButton) {
        if(m_scene->itemAt(pos, QTransform()) == NULL) {
            domain = new Domain(pos.x()-25, pos.y()-25);
            m_scene->addItem(domain);
        }
    }
    else if(event->button() == Qt::RightButton) {
        if(m_scene->itemAt(pos, QTransform()) == NULL) {
            //TODO: Add in the code to create the designed domain
        }
    }

    //Propogate the mouse event down to the domain objects
    QGraphicsView::mousePressEvent(event);
}
