#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

/*******************************************************************************
/*! \class graphicsview.h
 *
 *  Custom graphics view
*******************************************************************************/
#include <QComboBox>
#include <QGraphicsView>
#include <QMouseEvent>

#include "contextdata.h"
#include "domain.h"
#include "editdomain.h"
#include "interface.h"
#include "requirement.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView( QGraphicsScene *graphicsScene, ContextData *data,
                  QComboBox *diagram,
                  QWidget *parent=0);
    ~GraphicsView();

public slots:
    void mousePressEvent (QMouseEvent *event);
    void deleteDomain(Domain *dom);

signals:
    void updateDomainList(QStringList);
    void addItem(Domain *item);

public:
    QGraphicsScene *scene;

private:
    ContextData *context;
    QComboBox *diagram;

    bool drawingLine; //Unused
    QPointF startPos; //Unused
    QPointF endPos;   //Unused
    QLineF line;      //Unused

    Domain *domain;
    Interface *interface;
    Requirement *requirement;

    QStringList domainNames;
    QList<Domain *> domains;

    EditDomain *editDom;
};

#endif // GRAPHICSVIEW_H
