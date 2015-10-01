#include "editdomain.h"
#include "ui_editdomain.h"

EditDomain::EditDomain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDomain)
{
    ui->setupUi(this);
}

void EditDomain::setDomainName(QString name)
{
    ui->nameLineEdit->setText(name);
}

void EditDomain::setDomainDescription(QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

void EditDomain::setDomainType(QString type)
{
    if(type == "Designed")
        ui->designedRadio->setChecked(true);
    else
        ui->givenRadio->setChecked(true);
}

EditDomain::~EditDomain()
{
    delete ui;
}

void EditDomain::on_okButton_clicked()
{
    emit updateName(ui->nameLineEdit->text());
    emit updateDescription(ui->descriptionTextEdit->toPlainText());
    if(ui->designedRadio->isChecked())
        emit updateType("Designed");
    else
        emit updateType("Given");
    close();
}
