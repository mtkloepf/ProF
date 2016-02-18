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
    setFixedSize(geometry().width(), geometry().height());

    //Create the error message box for having duplicate connections
    errorMsg = new QMessageBox();

    //Turn off editing of phenomena names directly through the list view
    ui->phenomenaListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Add a "no connection" option for the combo boxes if it doesn't exist
    if(!domains.contains("None"))
        domains.append("None");

    //Create a model for the phenomena list view and set the prototype
    listModel = new QStringListModel();
    ui->phenomenaListView->setModel(listModel);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
EditInterface::~EditInterface()
{
    delete errorMsg;
    delete ui;
}

/*******************************************************************************
/*! \brief Sends the text of the description text edit to the interface once OK 
 *         is clicked
 *
 * @param desc the text held in the text edit
*******************************************************************************/
void EditInterface::setInterfaceDescription(const QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

/*******************************************************************************
/*! \brief Sends the text of the name line edit to the interface once OK is
 *         clicked
 *
 * @param name the text held in the name line edit
*******************************************************************************/
void EditInterface::setInterfaceName(const QString name)
{
    ui->nameLineEdit->setText(name);
}

/*******************************************************************************
/*! \brief Used to populate the list of domains to choose as connections
 *
 * @param names the list of domains that can be chosen as connections
*******************************************************************************/
void EditInterface::setDomainNames(const QStringList names)
{
    domains = names;
    ui->domainOne->addItems(domains);
    ui->domainTwo->addItems(domains);
}

/*******************************************************************************
/*! \brief Used to set the connections that already exist for the interface
 *
 * @param first  the first domain connection
 * @param second the second domain connection
*******************************************************************************/
void EditInterface::setConnections(const Domain *first, const Domain *second)
{
    if(first)
        ui->domainOne->setCurrentIndex(ui->domainOne->findText(first->getName()));
    if(second)
        ui->domainTwo->setCurrentIndex(ui->domainTwo->findText(second->getName()));
}

/*******************************************************************************
/*! \brief SLOT called when the OK button of this dialog is clicked
 *
 *  This function is used to send all data currently in the form to the
 *  interface
*******************************************************************************/
void EditInterface::on_okButton_clicked()
{
    emit updateName(ui->nameLineEdit->text());
    emit updateDescription(ui->descriptionTextEdit->toPlainText());

    //Domain connections must be unique and must have both or no connections
    if(ui->domainOne->currentText() == ui->domainTwo->currentText() &&
            (ui->domainOne->currentText() != "None" &&
             ui->domainTwo->currentText() != "None")) {
        errorMsg->setText("An interface must be "
                          "connected to two unique domains.");
        errorMsg->setStandardButtons(QMessageBox::Ok);
        errorMsg->setWindowTitle("Error");
        errorMsg->exec();
        return;
    }

    //Update the domain connections to the current combo box settings
    emit updateDomains(ui->domainOne->currentText(),
                       ui->domainTwo->currentText());
    close();
}

/*******************************************************************************
/*! \brief SLOT called when the Cancel button of this dialog is clicked
 *
 *  Exits the interface editing dialog.
 *  If called, NO data will be saved to the interface
*******************************************************************************/
void EditInterface::on_cancelButton_clicked()
{
    close();
}

/*******************************************************************************
/*! \brief SLOT called when the Reset button of this dialog is clicked
 *
 *  Resets all data in the form to NULL. Resets form to default interface values
*******************************************************************************/
void EditInterface::on_resetButton_clicked()
{
    ui->nameLineEdit->clear();
    ui->descriptionTextEdit->clear();
}
