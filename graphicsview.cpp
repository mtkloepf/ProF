#include "graphicsview.h"
#include "domain.h"

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
    if(m_scene->itemAt(pos, QTransform()) == NULL) {
        if(event->button() == Qt::LeftButton) {
            domain = new Domain(pos.x()-25, pos.y()-25);
            domain->setType("Given");
            m_scene->addItem(domain);
        }
        else if(event->button() == Qt::RightButton) {
            domain = new Domain(pos.x()-25, pos.y()-25);
            domain->setColor(Qt::yellow);
            domain->setType("Designed");
            m_scene->addItem(domain);
        }
        event->accept();
    }
    //Propogate the mouse event down to the domain objects
    else QGraphicsView::mousePressEvent(event);


}
