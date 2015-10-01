/*******************************************************************************
/*! \class machinedomain.cpp
 *
 *  Implementation of machine domain class
*******************************************************************************/
#include "machinedomain.h"

/*******************************************************************************
/*! \brief Constructor
*******************************************************************************/
MachineDomain::MachineDomain()
{
    setFlag(ItemIsMovable);
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
    return QRectF(0, 0, 100, 100);
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
    QBrush brush(Qt::red); // Machine domain will always be red
    painter->fillRect(boundingRect(), brush);
    painter->drawRect(boundingRect());
}
