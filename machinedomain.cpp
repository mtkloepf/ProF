/*******************************************************************************
/*! \class machinedomain.cpp
 *
 *  Custom graphics object to act as the machine domain. Similar behavior to the
 *  domain class, but cannot be deleted, can only have on instance, and has
 *  limited editing options
*******************************************************************************/
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "machinedomain.h"

/*******************************************************************************
/*! \brief Constructor
*******************************************************************************/
MachineDomain::MachineDomain()
    : pos(QPointF(0, 0))
{
    setFlag(ItemIsMovable);
    setColor(Qt::red);
    setDefaultColor(Qt::red);
    setAcceptHoverEvents(true);
    setName("Machine Domain");
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
MachineDomain::~MachineDomain() {}

/*******************************************************************************
/*! \brief Reimplemented qgraphicsitem function
 *
 *  Function used to determine the location of the object in scene coordinates
 *
 * @return the rectangle that the machine domain occupies in the scene
*******************************************************************************/
QRectF MachineDomain::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 75, 50);
}

/*******************************************************************************
/*! \brief Reimplemented qgraphicsitem function
 *
 *  Paints and updates the machine domain in the graphics scene when moved or
 *  created for the first time
 *
 * @param painter painter object that paints the machine domain
 * @param option --unused
 * @param widget --unused
*******************************************************************************/
void MachineDomain::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
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
QColor MachineDomain::getColor() const
{
    return color;
}
/*******************************************************************************
/*! \brief Sets the color the domain will be painted
 *
 * @param value color of the domain
*******************************************************************************/
void MachineDomain::setColor(const QColor &value)
{
    color = value;
}

/*******************************************************************************
/*! \brief Used to get the default color of the domain
 *   
 *  @return the default color of the domain
*******************************************************************************/
QColor MachineDomain::getDefaultColor() const
{
    return defaultColor;
}
/*******************************************************************************
/*! \brief Sets the default color of a domain
 *         
 *  @param value the color to set the default color to
*******************************************************************************/
void MachineDomain::setDefaultColor(const QColor &value)
{
    defaultColor = value;
}

/*******************************************************************************
/*! \brief Used for opening the context menu for the machine domain
 *
 *  Called when right clicking on the machine domain in the graphics scene.  
 *  Opens a context menu containing the edit option for the machine domain
 *
 * @param event the event that causes the context menu to appear (on windows it
 *        is right click)
*******************************************************************************/
void MachineDomain::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    //Create a new context menu to hold edit and delete actions
    //Connect the slot for editing the machine domain
    QMenu menu;
    QAction *editAction = menu.addAction("Edit");
    connect(editAction, SIGNAL(triggered()), this, SLOT(editDomain()));

    menu.exec(event->screenPos());
}

/*******************************************************************************
/*! \brief Domain mouse hover enter
 *
 *  Darkens the color of the domain that's currently hovered over. This makes it 
 *  easier for the use to see which domain is accepting the mouse
 *
 * @param event --unused
*******************************************************************************/
void MachineDomain::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor.darker(150));
    update();
}

/*******************************************************************************
/*! \brief Domain mouse hover exit
 *
 *  Resets the color of the domain to the default after the mouse leaves the 
 *  bounding rect
 *
 * @param event --unused
*******************************************************************************/
void MachineDomain::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor);
    update();
}

/*******************************************************************************
/*! \brief Retrieval for domain type
 *
 * @return QString containing the type of the domain
*******************************************************************************/
QString MachineDomain::getType() const
{
    return type;
}

/*******************************************************************************
/*! \brief SLOT function used for editing the domain. Attached to the context 
 *         menu for domains
*******************************************************************************/
void MachineDomain::editDomain()
{
    // Bring up the edit domain menu, connect the slots to the OK button of
    // the edit domain dialog, and give the current domain info for the
    // edit domain dialog to display
    edit = new EditDomain(0, true);
    edit->setDomainDescription(getDescription());
    edit->setDomainName(getName());
    edit->setDomainType(getType());
    connect(edit, SIGNAL(updateDescription(QString)),
            this, SLOT(setDescription(QString)));
    connect(edit, SIGNAL(updateName(QString)), this,
            SLOT(setName(QString)));

    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT function used for editing the domain. Attached to the context 
 *         menu for domains
*******************************************************************************/
QString MachineDomain::getName() const
{
    return name;
}
/*******************************************************************************
/*! \brief Setter for domain name
 *
 * @param value new name for the domain
*******************************************************************************/
void MachineDomain::setName(const QString &value)
{
    name = value;
}

/*******************************************************************************
/*! \brief Retrieval for domain description
 *
 * @return description as QString
*******************************************************************************/
QString MachineDomain::getDescription() const
{
    return description;
}
/*******************************************************************************
/*! \brief Setter for domain description
 *
 * @param value new text for the description
*******************************************************************************/
void MachineDomain::setDescription(const QString &value)
{
    description = value;
}

