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
    m_ContextView = new GraphicsView(new QGraphicsScene(), data, this);
    ui->centralWidget->layout()->addWidget(m_ContextView);

    //Create the machine domain and add it to the graphics view
    m_ContextView->scene->addItem(machine);

    connect(ui->ContextDiag, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(contextDiagToggled(bool)));

    connect(ui->ProblemDiag1, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag1Toggled(bool)));

    connect(ui->ProblemDiag2, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag2Toggled(bool)));

    connect(ui->ProblemDiag3, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag3Toggled(bool)));

    connect(ui->ProblemDiag4, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag4Toggled(bool)));

    connect(ui->ProblemDiag5, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag5Toggled(bool)));

    connect(ui->ProblemDiag6, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag6Toggled(bool)));

    connect(ui->ProblemDiag7, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag7Toggled(bool)));

    connect(ui->ProblemDiag8, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag8Toggled(bool)));

    connect(ui->ProblemDiag9, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag9Toggled(bool)));

    connect(ui->ProblemDiag10, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag10Toggled(bool)));

    connect(ui->ProblemDiag11, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag11Toggled(bool)));

    connect(ui->ProblemDiag12, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag12Toggled(bool)));

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
