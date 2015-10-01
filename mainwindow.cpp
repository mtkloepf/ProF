#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new GraphicsView(new QGraphicsScene(), this);
    ui->centralWidget->layout()->addWidget(view);

    machine = new MachineDomain();
    view->m_scene->addItem(machine);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    about = new About(this);
    about->show();
    about->raise();
    about->activateWindow();
}
