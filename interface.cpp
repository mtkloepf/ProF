/*******************************************************************************
/*! \class interface.cpp
 *
 *  Implementation for interfaces which connect to domains and are used to
 *  display common phenomena between the connections
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
Interface::Interface(int x, int y, QList<Domain *> &doms)
    : pos(QPointF(x, y)),
      domains(doms),
      firstDomain(NULL),
      secondDomain(NULL),
      defaultColor(Qt::green),
      enabled(true)
{
    setColor(defaultColor);
    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
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
void Interface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->setBrush(color);
    painter->drawEllipse(rec);
}

/*******************************************************************************
/*! \brief Returns the default color for interfaces
 *
 * @return the default color of the interface
*******************************************************************************/
QColor Interface::getDefaultColor() const
{
    return defaultColor;
}

/*******************************************************************************
/*! \brief Changes the default color of interfaces
 *
 * @param value the color to set the default color to
*******************************************************************************/
void Interface::setDefaultColor(const QColor &value)
{
    defaultColor = value;
}

/*******************************************************************************
/*! \brief Returns the color of the interface
 *
 * @return the current color of the interface
*******************************************************************************/
QColor Interface::getColor() const
{
    return color;
}

/*******************************************************************************
/*! \brief Changes the current color of interfaces
 *
 * @param value the color to set the current color to
*******************************************************************************/
void Interface::setColor(const QColor &value)
{
    color = value;
    update();
}


/*******************************************************************************
 * SLOT functions
/******************************************************************************/

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
    if(enabled) {
        QAction *editAction = menu.addAction("Edit");
        connect(editAction, SIGNAL(triggered()), this, SLOT(editInterface()));
        QAction *deleteAction = menu.addAction("Delete");
        connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteInterface()));
    }
    else {
        QAction *enableAction = menu.addAction("Enable");
        connect(enableAction, SIGNAL(triggered()), this, SLOT(disableInterface()));
    }
    menu.exec(event->screenPos());

}

/*******************************************************************************
/*! \brief Darkens the color of the interface when the mouse hovers over it
 *
 * @param event unused variable
*******************************************************************************/
void Interface::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor.darker(125));
    update();
}

/*******************************************************************************
/*! \brief Lightens the color of the interface when the mouse stops hovering
 *         over the interface
 *
 * @param event unused variable
*******************************************************************************/
void Interface::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor);
    update();
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

/*******************************************************************************
/*! \brief SLOT connected to context menu edit action
 *
 *  When edit is selected from the context menu, bring up a new dialog to edit
 *  the interface
*******************************************************************************/
void Interface::editInterface()
{
    // Bring up the edit interface menu, connect the slots to the OK button of
    // the edit domain dialog, and give the current interface info for the
    // edit interface dialog to display
    edit = new EditInterface(domains);
    edit->setInterfaceDescription(getDescription());
    edit->setInterfaceName(getName());
    edit->setDomainNames();
    edit->setConnections(firstDomain, secondDomain);
    edit->setDom1SharedPhenomena(dom1SharedPhenomena);
    edit->setDom2SharedPhenomena(dom2SharedPhenomena);
    connect(edit, SIGNAL(updateDescription(QString)),
            this, SLOT(setDescription(QString)));
    connect(edit, SIGNAL(updateName(QString)), this,
            SLOT(setName(QString)));
    connect(edit, SIGNAL(updateDomains(QString,QString)),
            this, SLOT(setDomains(QString,QString)));
    connect(edit, SIGNAL(updateDom1SharedPhenomena(QStringList)),
            this, SLOT(updateDom1SharedPhenomena(QStringList)));
    connect(edit, SIGNAL(updateDom2SharedPhenomena(QStringList)),
            this, SLOT(updateDom2SharedPhenomena(QStringList)));
    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT connected to context menu delete action
 *
 *  When delete is selected from the context menu, delete the interface
 *  from memory
*******************************************************************************/
void Interface::deleteInterface()
{
    delete this;
}

/*******************************************************************************
/*! \brief SLOT function intended to set the domain connections when the edit
 *         interface dialog is closed
 *
 *  @param first  String value for the name of the first domain connection
 *  @param second String value for the name of the second domain connection
*******************************************************************************/
void Interface::setDomains(const QString first, const QString second)
{
    bool firstFound, secondFound = false;

    //Cannot have only one connection
    if(first == "None" || second == "None") {
        firstDomain = NULL;
        secondDomain = NULL;
        return;
    }
    foreach(Domain * dom, domains) {
        if(first != "None" && dom->getName() == first) {
            firstDomain = dom;
            firstFound = true;
        }
        else if(second != "None" && dom->getName() == second) {
            secondDomain = dom;
            secondFound = true;
        }
        if(firstFound && secondFound) {
            emit connectionCreated(firstDomain, secondDomain);
            break;
        }
    }
}

void Interface::updateDom1SharedPhenomena(const QStringList phen)
{
    dom1SharedPhenomena = phen;
}

void Interface::updateDom2SharedPhenomena(const QStringList phen)
{
    dom2SharedPhenomena = phen;
}

int Interface::type() const
{
    return 2;
}

void Interface::disableInterface()
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

bool Interface::getEnabled()
{
    return enabled;
}
