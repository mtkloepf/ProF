#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_graphicsScene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(m_graphicsScene);
    machine = new MachineDomain();

    m_graphicsScene->addItem(machine);
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->GraphicsSceneMousePress == Qt::LeftButton)
        QDebug << "Left mouse button pressed in graphicsscene";
    if(event->button() == Qt::LeftButton) {
        //QPoint remapped = ui->graphicsView->mapFromParent( event->pos() );
        //if(ui->graphicsView->rect().contains( remapped )) {
            //QPointF mousePoint = ui->graphicsView->mapToScene( remapped );
            Domain *dom = new Domain(ui->graphicsView->mapFromParent( event->pos()));
            m_graphicsScene->addItem(dom);
            m_graphicsScene->update();
        //}
    }
}
