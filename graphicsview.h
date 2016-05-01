#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

/*******************************************************************************
/*! \class graphicsview.h
 *
 *  Custom graphics view
*******************************************************************************/
#include <QGraphicsView>
#include <QMouseEvent>

#include "contextdata.h"
#include "domain.h"
#include "editdomain.h"
#include "interface.h"
#include "problemdata.h"
#include "requirement.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView( QGraphicsScene *graphicsScene, ContextData *data,
                  QWidget *parent=0);
    ~GraphicsView();

    void clearProblemDiagrams(int diagNum);

public slots:
    void mousePressEvent (QMouseEvent *event);
    void deleteDomain(Domain *dom);

    void contextDiagToggled(bool state);
    void problemDiag1Toggled(bool state);
    void problemDiag2Toggled(bool state);
    void problemDiag3Toggled(bool state);
    void problemDiag4Toggled(bool state);
    void problemDiag5Toggled(bool state);
    void problemDiag6Toggled(bool state);
    void problemDiag7Toggled(bool state);
    void problemDiag8Toggled(bool state);
    void problemDiag9Toggled(bool state);
    void problemDiag10Toggled(bool state);
    void problemDiag11Toggled(bool state);
    void problemDiag12Toggled(bool state);

//    void lineAdded(QPointF pos1, QPointF pos2);

signals:
    void updateDomainList(QStringList);
    void addItem(Domain *item);

public:
    QGraphicsScene *scene;

private:
    int diagramNum;
    ContextData *context;
    QMap<int, ProblemData> requirements;

    Domain *domain;
    Interface *interface;
    Requirement *requirement;

    QStringList domainNames;
    QList<Domain *> domains;

    EditDomain *editDom;
};

#endif // GRAPHICSVIEW_H
