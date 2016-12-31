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

#include <qdebug.h>

/*******************************************************************************
/*! \brief Constructor for the domain
 *
 * @param x the x coordinate for the center of the domain in the scene
 * @param y the y coordinate for the center of the domain
*******************************************************************************/
Domain::Domain(float x, float y)
    : pos(QPointF(x, y)),
      enabled(true)
{
    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
    defaultColor = Qt::cyan;
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
/*! \brief Reimplemented function since domain derives from qgraphicsitem.
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
    painter->fillRect(boundingRect(), QBrush(color));
    painter->drawRect(boundingRect());
    painter->drawText(textRect, getName());
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
/*! \brief Sets the color the domain will be painted
 *
 * @param value color of the domain
*******************************************************************************/
void Domain::setColor(const QColor &value)
{
    color = value;
    update();
}

/*******************************************************************************
/*! \brief Used to get the default color of the domain
 *
 *  @return the default color of the domain
*******************************************************************************/
QColor Domain::getDefaultColor() const
{
    return defaultColor;
}
/*******************************************************************************
/*! \brief Sets the default color of a domain
 *
 *  @param value the color to set the default color to
*******************************************************************************/
void Domain::setDefaultColor(const QColor &value)
{
    defaultColor = value;
}

/*******************************************************************************
/*! \brief Retrieves the list of phenomena attached to this domain
 *
 * @return A list of phenomena
*******************************************************************************/
QList<Phenomenon> Domain::getPhenomena() const
{
    return phenomena;
}

/*******************************************************************************
/*! \brief Adds a phenomenon to the list associated with this domain
 *
 * @param phen the phenomenon to add to the domain
*******************************************************************************/
void Domain::addPhenomenon(const Phenomenon &phen) {
    phenomena.append(phen);
}

/*******************************************************************************
/*! \brief Removes a specific phenomenon associated with this domain
 *
 * @param phen the phenomenon to remove from the domain
*******************************************************************************/
void Domain::removePhenomenon(const Phenomenon &phen)
{
    phenomena.removeOne(phen);
}

/*******************************************************************************
/*! \brief Takes a domain as a parameter and copies all of its attributes into
 *         this domain
 *
 * @param dom the domain to copy the attributes from
*******************************************************************************/
void Domain::copyDomainAttributes(const Domain &dom)
{
    setName(dom.getName());
    setPhenomena(dom.getPhenomena());
    setType(dom.getType());
    setDescription(dom.getDescription());
}

/*******************************************************************************
/*! \brief The type of object within the graphics view
 *
 *  This value is used to to determine what object is active based on input
 *
 * @return the value corresponding to domain objects
*******************************************************************************/
int Domain::type() const
{
    return 3;
}

/*******************************************************************************
/*! \brief returns whether the domain is currently enabled
 *
 *  Domains are only disabled during construction of problem diagrams. They are
 *  always enabled in the context diagram
 *
 * @return true if enabled and false if disabled
*******************************************************************************/
bool Domain::getEnabled()
{
    return enabled;
}


/******************************************************************************/
/* Slot Functions
/******************************************************************************/


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
    //Then connect the signals to slot functions for the menu actions
    QMenu menu;
    if(enabled) {
        QAction *editAction = menu.addAction("Edit");
        connect(editAction, SIGNAL(triggered()), this, SLOT(editDomain()));
        QAction *deleteAction = menu.addAction("Delete");
        connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteDomain()));
        QAction *disableAction = menu.addAction("Disable");
        connect(disableAction, SIGNAL(triggered()), this, SLOT(disableDomain()));

        menu.exec(event->screenPos());
    }
    else {
        QAction *enable = menu.addAction("Enable");
        connect(enable, SIGNAL(triggered()), this, SLOT(disableDomain()));

        menu.exec(event->screenPos());
    }
}

/*******************************************************************************
/*! \brief Darkens the domain color when hovered over
 *
 *  Darkens the color of the domain that's currently hovered over. This makes it
 *  easier for the use to see which domain is accepting the mouse
 *
 * @param event --unused
*******************************************************************************/
void Domain::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    setColor(defaultColor.darker(125));
    update();
}

/*******************************************************************************
/*! \brief Lightens the domain color when hover event ends
 *
 *  Resets the color of the domain to the default after the mouse leaves the
 *  bounding rect
 *
 * @param event --unused
*******************************************************************************/
void Domain::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    setColor(defaultColor);
    update();
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
    return domainType;
}
/*******************************************************************************
/*! \brief Setter for domain type
 *
 * @param value the QString containing the type of domain to set to
*******************************************************************************/
void Domain::setType(const QString &value)
{
    //Change the type of the domain
    domainType = value;

    //Handle changing the color when the type changes
    if(value == "Designed") {
        setColor(Qt::yellow);
        setDefaultColor(Qt::yellow);
    }
    else {
        setColor(Qt::cyan);
        setDefaultColor(Qt::cyan);
    }
}

/*******************************************************************************
/*! \brief SLOT function used for editing the domain. Attached to the context 
 *         menu for domains
*******************************************************************************/
void Domain::editDomain()
{
    // Bring up the edit domain menu, connect the slots to the OK button of
    // the edit domain dialog, and give the current domain info for the
    // edit domain dialog to display
    edit = new EditDomain();
    edit->setDomainDescription(getDescription());
    edit->setDomainName(getName());
    edit->setDomainType(getType());
    edit->setPhenomena(phenomena);

    //Connect signals for updating the domain attributes for phenomena
    connect(edit, SIGNAL(updatePhenomena(QList<Phenomenon>)),
            this, SLOT(setPhenomena(QList<Phenomenon>)));
    connect(edit, SIGNAL(updateDescription(QString)),
            this, SLOT(setDescription(QString)));
    connect(edit, SIGNAL(updateName(QString)), this,
            SLOT(setName(QString)));
    connect(edit, SIGNAL(updateType(QString)), this,
            SLOT(setType(QString)));
    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT function used for deleting the domain. Attached to the context 
 *         menu for domains
*******************************************************************************/
void Domain::deleteDomain()
{
    emit deleteDomain(this);
    delete this;
}

/*******************************************************************************
/*! \brief SLOT function used for setting the list of phenomena owned by
 *         the domain
*******************************************************************************/
void Domain::setPhenomena(const QList<Phenomenon> &value)
{
    phenomena = value;
}

QPointF Domain::getPos()
{
    return pos;
}

void Domain::disableDomain()
{
    if(enabled) {
        setColor(Qt::gray);
        this->setAcceptHoverEvents(false);
        this->setAcceptedMouseButtons(Qt::NoButton);
        enabled = false;
    }
    else {
        setColor(defaultColor);
        this->setAcceptHoverEvents(true);
        this->setAcceptedMouseButtons(Qt::AllButtons);
        enabled = true;
    }
}
