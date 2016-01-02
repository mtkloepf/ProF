#include "editphenomenon.h"
#include "ui_editphenomenon.h"

EditPhenomenon::EditPhenomenon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPhenomenon)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(geometry().width(), geometry().height());
}

EditPhenomenon::~EditPhenomenon()
{
    delete ui;
}

void EditPhenomenon::setPhenonemonName(QString name)
{
    ui->nameLineEdit->setText(name);
}

void EditPhenomenon::setPhenomenonType(QString type)
{
    if(type == "Event") {
        ui->stateRadio->setChecked(false);
        ui->eventRadio->setChecked(true);
    }
    else if(type == "State") {
        ui->stateRadio->setChecked(true);
        ui->eventRadio->setChecked(false);
    }
}

void EditPhenomenon::setPhenomenonDesc(QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

void EditPhenomenon::on_okButton_clicked()
{
    Phenomenon phen("", "");
    phen.name = ui->nameLineEdit->text();
    if(ui->stateRadio->isChecked())
        phen.type = "State";
    else
        phen.type = "Event";
    phen.description = ui->descriptionTextEdit->toPlainText();
    emit updatePhenomenon(phen);

    close();
}

void EditPhenomenon::on_cancelButton_clicked()
{
    close();
}

void EditPhenomenon::on_resetButton_clicked()
{
    ui->descriptionTextEdit->setText("");
    ui->stateRadio->setChecked(true);
    ui->eventRadio->setChecked(false);
    ui->nameLineEdit->setText("");
}
