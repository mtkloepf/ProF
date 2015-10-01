/*******************************************************************************
/*! \class domain.cpp
 *
 *  Implementation of the domain. This class holds all information about
 *  the domain and the methods of using and changing domain data
 *
 *  Domains also have a method of creating the edit domain dialog
*******************************************************************************/
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "domain.h"

/*******************************************************************************
/*! \brief Constructor for the domain
 *
 * @param x the x coordinate for the center of the domain in the scene
 * @param y the y coordinate for the center of the domain
*******************************************************************************/
Domain::Domain(int x, int y)
    : pos(QPointF(x, y))
{
    setFlag(ItemIsMovable);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
Domain::~Domain() {}

/*******************************************************************************
/*! \brief Reimplemented function since domain inherits from qgraphicsitem
 *
 *  Function used to determine the location of the object in scene coordinates
 *
 * @return the rectangle that the domain occupies in the scene
*******************************************************************************/
QRectF Domain::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 75, 50);
}

/*******************************************************************************
/*! \brief Reimplemented function since domain inherits from qgraphicsitem.
 *
 *  Paints and updates the domain in the graphics scene when moved or created
 *  for the first time
 *
 * @param painter painter object that paints the domain
 * @param option --unused
 * @param widget --unused
*******************************************************************************/
void Domain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    QRectF textRect(pos.x()+5, pos.y()+5, 70, 45);
    QBrush brush(color);
    painter->fillRect(boundingRect(), brush);
    painter->drawRect(boundingRect());
    painter->drawText(textRect, getName());
}

/*******************************************************************************
/*! \brief Used for opening the context menu for domains
 *
 *  Called when right clicking on a domain in the graphics scene. Spawns a
 *  context menu containing the edit and delete options for the domain clicked
 *  on.
 *
 * @param event the event that causes the context menu to appear (on windows it
 *        is right click)
*******************************************************************************/
void Domain::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
        edit = new EditDomain();
        edit->setDomainDescription(getDescription());
        edit->setDomainName(getName());
        edit->setDomainType(getType());
        connect(edit, SIGNAL(updateDescription(QString)),
                this, SLOT(setDescription(QString)));
        connect(edit, SIGNAL(updateName(QString)), this,
                SLOT(setName(QString)));
        connect(edit, SIGNAL(updateType(QString)), this,
                SLOT(setType(QString)));

        edit->show();
        edit->raise();
        edit->activateWindow();
    }
}

/*******************************************************************************
/*! \brief Retrieval for domain description
 *
 * @return description as QString
*******************************************************************************/
QString Domain::getDescription() const
{
    return description;
}
/*******************************************************************************
/*! \brief Setter for domain description
 *
 * @param value new text for the description
*******************************************************************************/
void Domain::setDescription(const QString &value)
{
    description = value;
}


/*******************************************************************************
/*! \brief Retrieval for domain name
 *
 * @return the name of the domain
*******************************************************************************/
QString Domain::getName() const
{
    return name;
}
/*******************************************************************************
/*! \brief Setter for domain name
 *
 * @param value new name for the domain
*******************************************************************************/
void Domain::setName(const QString &value)
{
    name = value;
}


/*******************************************************************************
/*! \brief Retrieval for domain type
 *
 * @return QString containing the type of the domain
*******************************************************************************/
QString Domain::getType() const
{
    return type;
}
/*******************************************************************************
/*! \brief Setter for domain type
 *
 * @param value the QString containing the type of domain to set to
*******************************************************************************/
void Domain::setType(const QString &value)
{
    type = value;
    if(value == "Designed")
        setColor(Qt::yellow);
    else
        setColor(Qt::cyan);
}


/*******************************************************************************
/*! \brief Retrieval for the color the domain is painted
 *
 * @return color of the domain
*******************************************************************************/
QColor Domain::getColor() const
{
    return color;
}
/*******************************************************************************
/*! \brief Setter for domain color
 *
 * @param value new color for the domain
*******************************************************************************/
void Domain::setColor(const QColor &value)
{
    color = value;
}
