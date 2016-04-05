/*******************************************************************************
/*! \class mainwindow.cpp
 *
 *  Main window of the application
*******************************************************************************/
#include <QGraphicsScene>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent widget that parents this dialog
*******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    machine = new MachineDomain();
    //Data structure that stores every domain that exists
    data = new ContextData(machine);

    //Create the custom graphics view and add it to the main window
    QGraphicsScene *scene = new QGraphicsScene();
    m_ContextView = new GraphicsView(new QGraphicsScene(), data, true, this);
    m_ProblemView = new GraphicsView(new QGraphicsScene(), data, false, this);
    connect(m_ContextView, SIGNAL(addItem(Domain*)),
            this, SLOT(addItem(Domain*)));
    ui->centralWidget->layout()->addWidget(m_ContextView);
    ui->centralWidget->layout()->addWidget(m_ProblemView);

    //Create the machine domain and add it to the graphics view
    m_ContextView->scene->addItem(machine);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Slot called when the help->about is triggered
*******************************************************************************/
void MainWindow::on_actionAbout_triggered()
{
    about = new About(this);
    about->exec();
}

/*******************************************************************************
/*! \brief Slot called when the main window is closed
*******************************************************************************/
void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::addItem(Domain *item)
{
    Domain *item2 = new Domain(item->getPos().x(), item->getPos().y());
    item2->setParentItem(item);
    item2->copyDomainAttributes(*item);
    connect(item, SIGNAL(deleteDomain(Domain*)),
            item2, SLOT(deleteDomain()));
    m_ProblemView->scene->addItem(item2);
}

void MainWindow::updateDomain(Domain *item, QString prevName) {
    foreach(Domain *dom, data->getDomains()) {
        if(dom->getName() == prevName) {
            dom->copyDomainAttributes(*item);
        }
    }
}
