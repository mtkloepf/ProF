/*******************************************************************************
/*! \class interface.cpp
 *
 *  Implementation of the interface. This class holds all information about
 *  the interface and the methods of using and changing interface data
 *
 *  Interfaces also have a method of creating the edit interface dialog
*******************************************************************************/
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "interface.h"

/*******************************************************************************
/*! \brief Constructor for the interface
 *
 * @param x the x coordinate for the center of the interface in the scene
 * @param y the y coordinate for the center of the interface
*******************************************************************************/
Interface::Interface(int x, int y)
    : pos(QPointF(x, y))
{
    setFlag(ItemIsMovable);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
Interface::~Interface() {}

/*******************************************************************************
/*! \brief Reimplemented function since interface inherits from qgraphicsitem
 *
 *  Function used to determine the location of the object in scene coordinates
 *
 * @return the rectangle that the interface occupies in the scene
*******************************************************************************/
QRectF Interface::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 15, 15);
}

/*******************************************************************************
/*! \brief Reimplemented function since interface inherits from qgraphicsitem.
 *
 *  Paints and updates the interface in the graphics scene when moved or created
 *  for the first time
 *
 * @param painter painter object that paints the interface
 * @param option --unused
 * @param widget --unused
*******************************************************************************/
void Interface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->setBrush(Qt::green);
    painter->drawEllipse(rec);
}

/*******************************************************************************
/*! \brief Used for opening the context menu for interfaces
 *
 *  Called when right clicking on a interface in the graphics scene. Spawns a
 *  context menu containing the edit and delete options for the interface 
 *  clicked on.
 *
 * @param event the event that causes the context menu to appear (on windows it
 *        is right click)
*******************************************************************************/
void Interface::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    //Create a new context menu to hold edit and delete actions
    QMenu menu;
    QAction *editAction = menu.addAction("Edit");
    QAction *deleteAction = menu.addAction("Delete");

    //Delete the domain
    if(menu.exec( event->screenPos() ) == deleteAction) {
        delete this;
    }

    // Bring up the edit domain menu, connect the slots to the OK button of
    // the edit domain dialog, and give the current domain info for the
    // edit domain dialog to display
    else if(menu.exec( event->screenPos() ) == editAction) {
        edit = new EditInterface();
        edit->setInterfaceDescription(getDescription());
        edit->setInterfaceName(getName());
        connect(edit, SIGNAL(updateDescription(QString)),
                this, SLOT(setDescription(QString)));
        connect(edit, SIGNAL(updateName(QString)), this,
                SLOT(setName(QString)));

        edit->show();
        edit->raise();
        edit->activateWindow();
    }
}

/*******************************************************************************
/*! \brief Retrieval for interface description
 *
 * @return description as QString
*******************************************************************************/
QString Interface::getDescription() const
{
    return description;
}
/*******************************************************************************
/*! \brief Setter for interface description
 *
 * @param value new text for the description
*******************************************************************************/
void Interface::setDescription(const QString &value)
{
    description = value;
}

/*******************************************************************************
/*! \brief Retrieval for interface name
 *
 * @return the name of the interface
*******************************************************************************/
QString Interface::getName() const
{
    return name;
}
/*******************************************************************************
/*! \brief Setter for interface name
 *
 * @param value new name for the interface
*******************************************************************************/
void Interface::setName(const QString &value)
{
    name = value;
}

