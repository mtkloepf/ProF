/*******************************************************************************
/*! \class requirement.cpp
 *
 *  A custom graphics item used in problem diagrams to represent constraints
 *  put on the machine based on user demands and the relevant environmental
 *  attributes.
*******************************************************************************/
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "requirement.h"

Requirement::Requirement(float x, float y, ContextData *data)
    : pos(QPointF(x, y)),
      context(data)
{
    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
    defaultColor = Qt::magenta;
}

Requirement::~Requirement() {}

QRectF Requirement::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 75, 50);
}

void Requirement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2, Qt::DashLine));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(pos.x()+5, pos.y()+5, 70, 45);
}

QColor Requirement::getColor() const
{
    return color;
}

void Requirement::setColor(const QColor &value)
{
    color = value;
}

QColor Requirement::getDefaultColor() const
{
    return defaultColor;
}

void Requirement::setDefaultColor(const QColor &value)
{
    defaultColor = value;
}

void Requirement::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    //Create a new context menu to hold edit and delete actions
    //Then connect the signals to slot functions for the menu actions
    QMenu menu;
    QAction *editAction = menu.addAction("Edit");
    connect(editAction, SIGNAL(triggered()), this, SLOT(editRequirement()));
    QAction *deleteAction = menu.addAction("Delete");
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteRequirement()));

    menu.exec(event->screenPos());
}

void Requirement::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor.darker(125));
    update();
}

void Requirement::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setColor(defaultColor);
    update();
}

QString Requirement::getType() const
{
    return reqType;
}

void Requirement::setType(const QString &value)
{
    if(value == "Requirement") {
        setColor(Qt::magenta);
        setDefaultColor(Qt::magenta);
        reqType = "Requirement";
    }
    else {
        setColor("#1E90FF");
        setDefaultColor("#1E90FF");
        reqType = "Indicative Property";
    }
}

int Requirement::type() const
{
    return 1;
}

/*******************************************************************************
/*! \brief SLOT function used for editing the Requirement. Attached to the context
 *         menu for Requirements
*******************************************************************************/
void Requirement::editRequirement()
{
    // Bring up the edit Requirement menu, connect the slots to the OK button of
    // the edit Requirement dialog, and give the current Requirement info for the
    // edit Requirement dialog to display
    edit = new EditRequirement(context);
    edit->setRequirementDescription(getDescription());
    edit->setRequirementName(getName());
    edit->setRequirementType(getType());
    edit->setDomainNames(context->getDomainNames());
    edit->setConnections(firstDomain, secondDomain);
    edit->setDom1SharedPhenomena(dom1SharedPhenomena);
    edit->setDom2SharedPhenomena(dom2SharedPhenomena);
    connect(edit, SIGNAL(updateDescription(QString)),
            this, SLOT(setDescription(QString)));
    connect(edit, SIGNAL(updateName(QString)), this,
            SLOT(setName(QString)));
    connect(edit, SIGNAL(updateType(QString)),
            this, SLOT(setType(QString)));
    connect(edit, SIGNAL(updateDomains(QString,QString)),
            this, SLOT(setDomains(QString,QString)));
    connect(edit, SIGNAL(updateDom1SharedPhenomena(QList<Phenomenon>)),
            this, SLOT(updateDom1SharedPhenomena(QList<Phenomenon>)));
    connect(edit, SIGNAL(updateDom2SharedPhenomena(QList<Phenomenon>)),
            this, SLOT(updateDom2SharedPhenomena(QList<Phenomenon>)));
    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT function used for deleting the Requirement. Attached to the context
 *         menu for Requirements
*******************************************************************************/
void Requirement::deleteRequirement()
{
    delete this;
}

/*******************************************************************************
/*! \brief Retrieval for domain description
 *
 * @return description as QString
*******************************************************************************/
QString Requirement::getDescription() const
{
    return description;
}
/*******************************************************************************
/*! \brief Setter for domain description
 *
 * @param value new text for the description
*******************************************************************************/
void Requirement::setDescription(const QString &value)
{
    description = value;
}

/*******************************************************************************
/*! \brief Retrieval for domain name
 *
 * @return the name of the domain
*******************************************************************************/
QString Requirement::getName() const
{
    return name;
}
/*******************************************************************************
/*! \brief Setter for domain name
 *
 * @param value new name for the domain
*******************************************************************************/
void Requirement::setName(const QString &value)
{
    name = value;
}

/*******************************************************************************
/*! \brief SLOT function intended to set the domain connections when the edit
 *         interface dialog is closed
 *
 *  @param first  String value for the name of the first domain connection
 *  @param second String value for the name of the second domain connection
*******************************************************************************/
void Requirement::setDomains(const QString first, const QString second)
{
    if(first != "None")
        firstDomain = context->findDomain(first);
    else
        firstDomain = NULL;
    if(second != "None")
        secondDomain = context->findDomain(second);
    else
        secondDomain = NULL;
}

void Requirement::updateDom1SharedPhenomena(QList<Phenomenon> phen)
{
    dom1SharedPhenomena = phen;
}

void Requirement::updateDom2SharedPhenomena(QList<Phenomenon> phen)
{
    dom2SharedPhenomena = phen;
}

