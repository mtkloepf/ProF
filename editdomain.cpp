#include "editdomain.h"
#include "ui_editdomain.h"

EditDomain::EditDomain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDomain)
{
    ui->setupUi(this);
}

EditDomain::~EditDomain()
{
    delete ui;
}
