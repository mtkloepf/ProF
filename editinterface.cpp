/*******************************************************************************
/*! \class editinterface.cpp
 *
 *  Dialog used for editing interface properties. The fields of the dialog are
 *  initially populated from the domain creating this dialog. Once the OK
 *  button is clicked, this dialog sends the changes to the interface to update
 *  data
*******************************************************************************/
#include "editinterface.h"
#include "ui_editinterface.h"

/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent widget that parents this dialog
*******************************************************************************/
EditInterface::EditInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInterface)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->withArrowRadio->setVisible(false);
    ui->withoutArrowRadio->setVisible(false);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
EditInterface::~EditInterface()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Sends the text of the description text edit to the interface once OK 
 *         is clicked
 *
 * @param desc the text held in the text edit
*******************************************************************************/
void EditInterface::setInterfaceDescription(QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

/*******************************************************************************
/*! \brief Sends the text of the name line edit to the interface once OK is
 *         clicked
 *
 * @param name the text held in the name line edit
*******************************************************************************/
void EditInterface::setInterfaceName(QString name)
{
    ui->nameLineEdit->setText(name);
}

/*******************************************************************************
/*! \brief Slot called when the OK button of this dialog is clicked
 *
 *  This function is used to send all data currently in the form to the 
 *  interface
*******************************************************************************/
void EditInterface::on_okButton_clicked()
{
    emit updateName(ui->nameLineEdit->text());
    emit updateDescription(ui->descriptionTextEdit->toPlainText());
    close();
}

/*******************************************************************************
/*! \brief Slot called when the Cancel button of this dialog is clicked
 *
 *  Exits the interface editing dialog.
 *  If called, NO data will be saved to the interface
*******************************************************************************/
void EditInterface::on_cancelButton_clicked()
{
    close();
}

/*******************************************************************************
/*! \brief Slot called when the Reset button of this dialog is clicked
 *
 *  Resets all data in the form to NULL. Resets form to default interface values
*******************************************************************************/
void EditInterface::on_resetButton_clicked()
{
    ui->nameLineEdit->clear();
    ui->descriptionTextEdit->clear();
}
