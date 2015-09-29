#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "machinedomain.h"
#include "domain.h"
#include "graphicsview.h"
#include <QMouseEvent>
#include <QList>

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
    GraphicsView *view;

public slots:
    void on_actionAbout_triggered();

private slots:
    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
    About *about;
    MachineDomain *machine;
    QList<Domain> domains;


};

#endif // MAINWINDOW_H
