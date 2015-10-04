/*******************************************************************************
/*! \class about.cpp
 *
 *  The dialog created from selecting Help->About in the main toolbar
*******************************************************************************/
#include "about.h"
#include "ui_about.h"

/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent the widget that parents the about dialog
*******************************************************************************/
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(geometry().width(), geometry().height());
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
About::~About()
{
    delete ui;
}
