#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*******************************************************************************
/*! \class mainwindow.h
 *
 *  The main window of the application
*******************************************************************************/
#include <QMainWindow>

#include "about.h"
#include "graphicsview.h"
#include "machinedomain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    GraphicsView *m_view;

public slots:
    void on_actionAbout_triggered();
    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
    About *about;
    MachineDomain *machine;
};

#endif // MAINWINDOW_H
