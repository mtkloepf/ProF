/*******************************************************************************
/*! \class graphicsview.cpp
 *
 *  Custom graphics view used for displaying the machine domain and any
 *  other domains
*******************************************************************************/
#include <QMenu>

#include "graphicsview.h"

#include <qdebug.h>

/*******************************************************************************
/*! \brief Constructor
 *
 * @param graphicsScene the scene to attach to this graphics view
 * @param parent        widget that parents this dialog
*******************************************************************************/
GraphicsView::GraphicsView( QGraphicsScene *graphicsScene, ContextData *data,
                            QComboBox *diagram,
                            QWidget *parent)
    : QGraphicsView( graphicsScene, parent),
      context(data),
      scene(graphicsScene),
      diagram(diagram)
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

    //Context diagrams have domains and interfaces
    if(diagram->currentText() == "Context Diagram") {

        //Check to see if we are clicking on an empty space in the scene
        //We do not want to spawn another domain if clicking on a current one
        if(scene->itemAt(pos, QTransform()) == NULL) {
            if(event->button() == Qt::LeftButton) {
                //Create a new given domain and center it on the mouse
                domain = new Domain(pos.x()-25, pos.y()-25);
                domain->setType("Given");

                connect(domain, SIGNAL(deleteDomain(Domain*)),
                        this, SLOT(deleteDomain(Domain*)));

                QString name = QString("Domain %1").arg(context->getDomainCount());
                domain->setName(name);
                context->addDomain(*domain);
                scene->addItem(domain);
                emit addItem(domain);
            }
            else if(event->button() == Qt::RightButton) {
                //Create a new interface and center it on the mouse
                interface = new Interface(pos.x()-7.5, pos.y()-7.5, context);
                scene->addItem(interface);
            }
        }
        //Propogate the mouse event down to the scene objects
        else QGraphicsView::mousePressEvent(event);

    }
    else {
        //Problem diagrams have requirements
        if(scene->itemAt(pos, QTransform()) == NULL) {
            if(event->button() == Qt::LeftButton) {
                requirement = new Requirement(pos.x()-25, pos.y()-25);
                requirement->setType("Requirement");
                scene->addItem(requirement);
            }
        }
        //Propogate the mouse event down to the scene objects
        else QGraphicsView::mousePressEvent(event);
    }
}

/*******************************************************************************
/*! \brief Removes a domain from the context data once a domain deletes itself
 *
 * @param dom a pointer to the domain to be removed
*******************************************************************************/
void GraphicsView::deleteDomain(Domain *dom)
{
    //If the domain to be removed exists in the context, remove it
    if(context->getDomains().contains(dom)) {
        context->removeDomain(*dom);
    }

    foreach(Interface *interface, context->getInterfaces()) {
        if(interface->getFirstDomain() == dom) interface->setFirstDomain(NULL);
        else if(interface->getSecondDomain() == dom) interface->setSecondDomain(NULL);
    }
}
