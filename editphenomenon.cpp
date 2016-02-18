/*******************************************************************************
/*! \class editphenomenon.cpp
 *
 *  Dialog that appears in order to edit the properties of the selected
 *  phenomenon
*******************************************************************************/
#include "editphenomenon.h"
#include "ui_editphenomenon.h"

/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent widget that parents this dialog
*******************************************************************************/
EditPhenomenon::EditPhenomenon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPhenomenon)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(geometry().width(), geometry().height());
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
EditPhenomenon::~EditPhenomenon()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Sets the name of a phenomenon
 *
 * @param name the name of the phenomenon to set the line edit to
*******************************************************************************/
void EditPhenomenon::setPhenonemonName(const QString name)
{
    ui->nameLineEdit->setText(name);
}

/*******************************************************************************
/*! \brief Sets the type of a phenomenon
 *
 * @param type the type of the phenomenon to set radio buttons to
*******************************************************************************/
void EditPhenomenon::setPhenomenonType(const QString type)
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

/*******************************************************************************
/*! \brief Sets the name of a phenomenon
 *
 * @param desc the description of the phenomenon
*******************************************************************************/
void EditPhenomenon::setPhenomenonDesc(const QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

/*******************************************************************************
/*! \brief SLOT function when the OK button is clicked. Updates phenomenon
 *         attributes
*******************************************************************************/
void EditPhenomenon::on_okButton_clicked()
{
    //Do not allow for empty names for phenomena
    if(ui->nameLineEdit->text() == "") {
        close();
    }

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

/*******************************************************************************
/*! \brief SLOT function when the cancel button is clicked. No attributes saved
*******************************************************************************/
void EditPhenomenon::on_cancelButton_clicked()
{
    close();
}

/*******************************************************************************
/*! \brief SLOT function when the reset button is clicked. Form data is cleared
*******************************************************************************/
void EditPhenomenon::on_resetButton_clicked()
{
    ui->descriptionTextEdit->setText("");
    ui->stateRadio->setChecked(true);
    ui->eventRadio->setChecked(false);
    ui->nameLineEdit->setText("");
}
