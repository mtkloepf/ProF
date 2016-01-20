/*******************************************************************************
/*! \class graphicsview.cpp
 *
 *  Custom graphics view used for displaying the machine domain and any
 *  other domains
*******************************************************************************/
#include "graphicsview.h"

/*******************************************************************************
/*! \brief Constructor
 *
 * @param graphicsScene the scene to attach to this graphics view
 * @param parent        widget that parents this dialog
*******************************************************************************/
GraphicsView::GraphicsView( QGraphicsScene *graphicsScene, QWidget *parent)
    : QGraphicsView( graphicsScene, parent),
      scene(graphicsScene)
{
    setScene(scene);
    setMouseTracking(true);
    viewport()->setMouseTracking(true);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
GraphicsView::~GraphicsView() {}

/*******************************************************************************
/*! \brief handles mouse events on the scene
 *
 *   Mouse handling for the scene. If the event is a left click a given domain
 *   is created. If the event is a right click a designed domain is created.
 *   All other mouse events are ignored by the graphics view and propogated to
 *   the scene to be handled.
 *
 * @param event the mouse event triggered on the view
*******************************************************************************/
void GraphicsView::mousePressEvent( QMouseEvent *event)
{
    //Get the coordinates of the mouse event from the scene
    QPointF pos = mapToScene( event->pos() );

    //Check to see if we are clicking on an empty space in the scene
    //We do not want to spawn another domain if clicking on a current one
    if(scene->itemAt(pos, QTransform()) == NULL) {
        if(event->button() == Qt::LeftButton) {
            //Create a new given domain and center it on the mouse
            domain = new Domain(pos.x()-25, pos.y()-25);
            domain->setType("Given");
            domains.append(domain->getName());
            connect(domain, SIGNAL(updateName(QString,QString)),
                    this, SLOT(updateDomainNames(QString,QString)));
            scene->addItem(domain);
        }
        else if(event->button() == Qt::RightButton) {
            //Create a new given domain and center it on the mouse
            domain = new Domain(pos.x()-25, pos.y()-25);
            domain->setType("Designed");
            domains.append(domain->getName());
            connect(domain, SIGNAL(updateName(QString,QString)),
                    this, SLOT(updateDomainNames(QString,QString)));
            scene->addItem(domain);
        }
        else if(event->button() == Qt::MiddleButton) {
            //Create a new interface and center it on the mouse
            interface = new Interface(pos.x()-7.5, pos.y()-7.5);
            interface->updateDomains(domains);
            connect(this, SIGNAL(updateDomainList(QStringList)),
                    interface, SLOT(updateDomains(QStringList)));
            scene->addItem(interface);
        }
        event->accept();
    }
    //Propogate the mouse event down to the domain objects
    else QGraphicsView::mousePressEvent(event);
}

void GraphicsView::updateDomainNames(QString prev, QString current)
{
    for(int i = 0; i < domains.size(); i++) {
        if(domains.at(i) == prev) {
            domains.replace(i, current);
            break;
        }
    }
    emit updateDomainList(domains);
}
