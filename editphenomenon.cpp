#include "editphenomenon.h"
#include "ui_editphenomenon.h"

EditPhenomenon::EditPhenomenon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPhenomenon)
{
    ui->setupUi(this);
}

EditPhenomenon::~EditPhenomenon()
{
    delete ui;
}
