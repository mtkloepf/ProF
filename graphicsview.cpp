/*******************************************************************************
/*! \class graphicsview.cpp
 *
 *  Custom graphics view used for displaying the machine domain and any
 *  other domains
*******************************************************************************/
#include <QMenu>

#include "graphicsview.h"

/*******************************************************************************
/*! \brief Constructor
 *
 * @param graphicsScene the scene to attach to this graphics view
 * @param parent        widget that parents this dialog
*******************************************************************************/
GraphicsView::GraphicsView( QGraphicsScene *graphicsScene, ContextData &data,
                            QWidget *parent)
    : QGraphicsView( graphicsScene, parent),
      context(data),
      scene(graphicsScene),
      diagramNum(0)
{
    setScene(scene);
    setMouseTracking(true);
    viewport()->setMouseTracking(true);

    //    connect(context, SIGNAL(lineAdded(QPointF,QPointF)),
    //            this, SLOT(lineAdded(QPointF,QPointF)));
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
GraphicsView::~GraphicsView() {}

void GraphicsView::clearProblemDiagrams(int diagNum)
{
    requirements[diagNum].clearRequirements();
}

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
    if(diagramNum == 0) {

        //Check to see if we are clicking on an empty space in the scene
        //We do not want to spawn another domain if clicking on a current one
        if(scene->itemAt(pos, QTransform()) == NULL) {
            if(event->button() == Qt::LeftButton) {
                //Create a new given domain and center it on the mouse
                domain = new Domain(pos.x()-25, pos.y()-25);
                domain->setDomainType("Given");

                connect(domain, SIGNAL(deleteDomain(Domain*)),
                        this, SLOT(deleteDomain(Domain*)));

                QString name = QString("Domain %1").arg(context.getDomainCount());
                domain->setName(name);
                context.addDomain(*domain);
                scene->addItem(domain);
            }
            else if(event->button() == Qt::RightButton) {
                //Create a new interface and center it on the mouse
                interface = new Interface(pos.x()-7.5, pos.y()-7.5, context.getDomains());

                connect(interface, SIGNAL(connectionCreated(Domain*,Domain*)),
                        this, SLOT(connectDomains(Domain*, Domain*)));

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
                requirement = new Requirement(pos.x()-25, pos.y()-25, &context);
                requirement->setType("Requirement");
                requirements[diagramNum].addRequirement(*requirement);

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
    if(context.getDomains().contains(dom)) {
        context.removeDomain(*dom);
    }

    //    foreach(Interface *interface, context.getInterfaces()) {
    //        if(interface->getFirstDomain() == dom) interface->setFirstDomain(NULL);
    //        else if(interface->getSecondDomain() == dom) interface->setSecondDomain(NULL);
    //    }
}

void GraphicsView::contextDiagToggled(bool state)
{
    if(state) {
        diagramNum=0;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 3) {
                qgraphicsitem_cast<Domain *>(item)->disableDomain();
                item->show();
            }
            else if(item->type() == 2) {
                qgraphicsitem_cast<Interface *>(item)->disableInterface();
                item->show();
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 3) {
                if(qgraphicsitem_cast<Domain *>(item)->getEnabled())
                    qgraphicsitem_cast<Domain *>(item)->disableDomain();
            }
            else if(item->type() == 2 ) {
                if(qgraphicsitem_cast<Interface *>(item)->getEnabled())
                    qgraphicsitem_cast<Interface *>(item)->disableInterface();
            }
        }
    }
}

void GraphicsView::problemDiag1Toggled(bool state)
{
    if(state) {
        diagramNum=1;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag2Toggled(bool state)
{
    if(state) {
        diagramNum=2;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag3Toggled(bool state)
{
    if(state) {
        diagramNum=3;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag4Toggled(bool state)
{
    if(state) {
        diagramNum=4;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag5Toggled(bool state)
{
    if(state) {
        diagramNum=5;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag6Toggled(bool state)
{
    if(state) {
        diagramNum=6;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag7Toggled(bool state)
{
    if(state) {
        diagramNum=7;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag8Toggled(bool state)
{
    if(state) {
        diagramNum=8;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag9Toggled(bool state)
{
    if(state) {
        diagramNum=9;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag10Toggled(bool state)
{
    if(state) {
        diagramNum=10;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag11Toggled(bool state)
{
    if(state) {
        diagramNum=11;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::problemDiag12Toggled(bool state)
{
    if(state) {
        diagramNum=12;
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type() == 1) {
                if(requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->show();
                }
                else if(!requirements.value(diagramNum).getRequirements()
                        .contains(qgraphicsitem_cast<Requirement *>(item))) {
                    item->hide();
                }
            }
        }
    }
    else {
        foreach(QGraphicsItem *item, scene->items()) {
            if(item->type()== 1) item->hide();
        }
    }
}

void GraphicsView::connectDomains(Domain *first, Domain *second)
{
    //TODO: We have the connected domains, now draw a line between them!
    //QLineF line(first->boundingRect().center(), second->boundingRect().center());
    //scene->addLine(line);
}

//void GraphicsView::lineAdded(QPointF pos1, QPointF pos2)
//{
//    qDebug() << "Drawing line";
//    qDebug() << "Point 1: " << pos1.x() << ", " << pos1.y();
//    qDebug() << "Point 2: " << pos2.x() << ", " << pos2.y();
//    QLineF line(pos1, pos2);
//    scene->addLine(line);
//    update();

//    foreach(QLineF line, context->getLines()) {
//        scene->addLine(line);
//    }
//}
