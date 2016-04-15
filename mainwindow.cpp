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
    //Data structure that stores all relevant items for the diagrams
    data = new ContextData(machine);

    //Create the custom graphics view and add it to the main window
    m_ContextView = new GraphicsView(new QGraphicsScene(), data, ui->diagramCombo, this);
    ui->centralWidget->layout()->addWidget(m_ContextView);

    //Create the machine domain and add it to the graphics view
    m_ContextView->scene->addItem(machine);

    connect(ui->addDiagramButton, SIGNAL(clicked(bool)),
            this, SLOT(addProblemDiagram()));
    connect(ui->DeleteDiagramButton, SIGNAL(clicked(bool)),
            this, SLOT(deleteProblemDiagram()));
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

void MainWindow::addProblemDiagram()
{
    ui->diagramCombo->addItem(QString("Problem Diagram %1").arg(ui->diagramCombo->count()-1));
    ui->diagramCombo->setCurrentIndex(ui->diagramCombo->count()-1);
}

void MainWindow::deleteProblemDiagram()
{
    if(ui->diagramCombo->currentText() != "Context Diagram") {
        ui->diagramCombo->removeItem(ui->diagramCombo->currentIndex());
    }
}
