#ifndef ABOUT_H
#define ABOUT_H

/*******************************************************************************
/*! \class about.h
 *
 *  The about dialog displays information regarding the project to the user
*******************************************************************************/
#include <QDialog>
#include <QWidget>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
