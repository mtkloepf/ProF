/*******************************************************************************
/*! \class mainwindow.cpp
 *
 *  Main window of the application
*******************************************************************************/
#include <QGraphicsScene>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>
#include <qgroupbox.h>

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

    problemDiagrams.setExclusive(true);
    problemDiagrams.addButton(ui->ContextDiag, 0);
    problemDiagrams.addButton(ui->ProblemDiag1, 1);
    problemDiagrams.addButton(ui->ProblemDiag2, 2);
    problemDiagrams.addButton(ui->ProblemDiag3, 3);
    problemDiagrams.addButton(ui->ProblemDiag4, 4);
    problemDiagrams.addButton(ui->ProblemDiag5, 5);
    problemDiagrams.addButton(ui->ProblemDiag6, 6);
    problemDiagrams.addButton(ui->ProblemDiag7, 7);
    problemDiagrams.addButton(ui->ProblemDiag8, 8);
    problemDiagrams.addButton(ui->ProblemDiag9, 9);
    problemDiagrams.addButton(ui->ProblemDiag10, 10);
    problemDiagrams.addButton(ui->ProblemDiag11, 11);
    problemDiagrams.addButton(ui->ProblemDiag12, 12);

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(addProblemDiagram()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)),
            this, SLOT(deleteProblemDiagram()));

    connect(ui->ContextDiag, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(contextDiagToggled(bool)));

    connect(ui->ProblemDiag1, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag1Toggled(bool)));

    connect(ui->ProblemDiag2, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag2Toggled(bool)));
    ui->ProblemDiag2->setVisible(false);

    connect(ui->ProblemDiag3, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag3Toggled(bool)));
    ui->ProblemDiag3->setVisible(false);


    connect(ui->ProblemDiag4, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag4Toggled(bool)));
    ui->ProblemDiag4->setVisible(false);


    connect(ui->ProblemDiag5, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag5Toggled(bool)));
    ui->ProblemDiag5->setVisible(false);


    connect(ui->ProblemDiag6, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag6Toggled(bool)));
    ui->ProblemDiag6->setVisible(false);


    connect(ui->ProblemDiag7, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag7Toggled(bool)));
    ui->ProblemDiag7->setVisible(false);


    connect(ui->ProblemDiag8, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag8Toggled(bool)));
    ui->ProblemDiag8->setVisible(false);


    connect(ui->ProblemDiag9, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag9Toggled(bool)));
    ui->ProblemDiag9->setVisible(false);


    connect(ui->ProblemDiag10, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag10Toggled(bool)));
    ui->ProblemDiag10->setVisible(false);


    connect(ui->ProblemDiag11, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag11Toggled(bool)));
    ui->ProblemDiag11->setVisible(false);


    connect(ui->ProblemDiag12, SIGNAL(toggled(bool)),
            m_ContextView, SLOT(problemDiag12Toggled(bool)));
    ui->ProblemDiag12->setVisible(false);
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
    foreach(QAbstractButton *radio, problemDiagrams.buttons()) {
        if(!radio->isVisible()) {
            radio->setVisible(true);
            break;
        }
    }
}

void MainWindow::deleteProblemDiagram()
{
    int checked = problemDiagrams.checkedId();
    if(checked != 0) {
        problemDiagrams.button(checked)->setVisible(false);
        m_ContextView->clearProblemDiagrams(checked);
        problemDiagrams.button(0)->setChecked(true);
    }

}
