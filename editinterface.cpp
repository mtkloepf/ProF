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

#include <qdebug.h>

/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent widget that parents this dialog
*******************************************************************************/
EditInterface::EditInterface(const QList<Domain *> &domains, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInterface),
    domains(domains)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->withArrowRadio->setVisible(false);
    ui->withoutArrowRadio->setVisible(false);
    setFixedSize(geometry().width(), geometry().height());

    //Create the error message box for having duplicate connections
    errorMsg = new QMessageBox();
    errorMsg->setAttribute(Qt::WA_DeleteOnClose);

    //Turn off editing of phenomena names directly through the list view
    ui->domain1SharedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->domain2SharedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create a model for the phenomena list view and set the prototype
    dom1SharedListModel = new QStringListModel();
    dom2SharedListModel = new QStringListModel();
    ui->domain1SharedListView->setModel(dom1SharedListModel);
    ui->domain2SharedListView->setModel(dom2SharedListModel);

    connect(ui->domainOne, SIGNAL(currentIndexChanged(int)),
            this, SLOT(domain1ConnectionChanged()));
    connect(ui->domainTwo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(domain2ConnectionChanged()));
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
void EditInterface::setDomainNames()
{
    QStringList domainNames;
    foreach(Domain * dom, domains) {
        domainNames.append(dom->getName());
    }
    ui->domainOne->addItems(domainNames);
    ui->domainTwo->addItems(domainNames);
}

/*******************************************************************************
/*! \brief Used to set the connections that already exist for the interface
 *
 * @param first  the first domain connection
 * @param second the second domain connection
*******************************************************************************/
void EditInterface::setConnections(const Domain *first, const Domain *second)
{
    if(first != NULL)
        if(ui->domainOne->findText(first->getName()) != -1)
            ui->domainOne->setCurrentIndex(ui->domainOne->
                                           findText(first->getName()));
        else if(first == NULL)
            ui->domainOne->setCurrentIndex(ui->domainOne->
                                           findText("None"));
    if(second != NULL)
        if(ui->domainTwo->findText(second->getName()) != -1)
            ui->domainTwo->setCurrentIndex(ui->domainTwo->
                                           findText(second->getName()));
        else if(second == NULL)
            ui->domainTwo->setCurrentIndex(ui->domainTwo->
                                           findText("None"));
}

/*******************************************************************************
/*! \brief Adds any shared phenomena from domain one to the list
 *
 *         The list is compiled by the calling interface and displayed here
 *
 * @param phen  list of all shared phenomena coming from domain one
*******************************************************************************/
void EditInterface::setDom1SharedPhenomena(const QStringList &phen)
{
    dom1SharedListModel->setStringList(phen);
}

/*******************************************************************************
/*! \brief Adds any shared phenomena from domain two to the list
 *
 *         The list is compiled by the calling interface and displayed here
 *
 * @param phen  list of all shared phenomena coming from domain two
*******************************************************************************/
void EditInterface::setDom2SharedPhenomena(const QStringList &phen)
{
    dom2SharedListModel->setStringList(phen);
}

/*******************************************************************************
/*! \brief SLOT called when the editing of shared phenomena for a domain one
 *         is complete
 *
 *  @param phen The updated list of shared phenomena to display for domain one
*******************************************************************************/
void EditInterface::updateDomain1SharedPhenomena(const QStringList phen)
{
    dom1SharedPhenomena = phen;
    dom1SharedListModel->setStringList(dom1SharedPhenomena);
}

/*******************************************************************************
/*! \brief SLOT called when the editing of shared phenomena for a domain two
 *         is complete
 *
 *  @param phen The updated list of shared phenomena to display for domain two
*******************************************************************************/
void EditInterface::updateDomain2SharedPhenomena(const QStringList phen)
{
    dom2SharedPhenomena = phen;
    dom2SharedListModel->setStringList(dom2SharedPhenomena);
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
    else {
        //QPointF pos1 = data->findDomain(ui->domainOne->currentText())->getPos();
        // QPointF pos2 = data->findDomain(ui->domainOne->currentText())->getPos();
    }

    //Update the domain connections to the current combo box settings
    emit updateDomains(ui->domainOne->currentText(),
                       ui->domainTwo->currentText());
    emit updateDom1SharedPhenomena(dom1SharedPhenomena);
    emit updateDom2SharedPhenomena(dom2SharedPhenomena);

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
/*! \brief SLOT called when the button for editing shared phenomena for domain
 *         one is clicked
 *
 *  The new dialog is sent all the current information about the shared and
 *  unshared phenomena based on domain one (as set in the combo box in the UI)
*******************************************************************************/
void EditInterface::on_editDom1Phen_clicked()
{
    QStringList unshared; //List of unshared phenomena
    QStringList shared;   //List of shared phenomena

    //Get the phenomena for domain 1
    QList<Phenomenon> unsharedPhen;
    foreach(Domain *dom, domains) {
        if(dom->getName() == ui->domainOne->currentText()) {
            unsharedPhen = dom->getPhenomena();
            break;
        }
    }

    // Create the list of unshared phenomena by removing the shared ones from
    // the list of all phenomena owned by the domain
    foreach(Phenomenon phenomenon, unsharedPhen) {        //Domain 1 Phenomena
        foreach(QString phenom, dom1SharedPhenomena) { //Currently shared
            if(phenomenon.name == phenom) {
                unsharedPhen.removeOne(phenomenon);
                shared.append(phenom); //Build the shared phonomena list
            }
        }
    }

    // Build the list for unshared phenomena
    foreach(Phenomenon phenomenon, unsharedPhen) {
        unshared.append(phenomenon.name);
    }

    edit = new EditSharedPhenomenon(true);

    connect(edit, SIGNAL(updateDomain1SharedPhenomena(QStringList)),
            this, SLOT(updateDomain1SharedPhenomena(QStringList)));

    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->setSharedPhenomena(shared);
    edit->setUnsharedPhenomena(unshared);
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT called when the button for editing shared phenomena for domain
 *         two is clicked
 *
 *  The new dialog is sent all the current information about the shared and
 *  unshared phenomena based on domain two (as set in the combo box in the UI)
*******************************************************************************/
void EditInterface::on_editDom2Phen_clicked()
{
    QStringList unshared; //List of unshared phenomena
    QStringList shared;   //List of shared phenomena

    //Get the phenomena for domain 2
    QList<Phenomenon> unsharedPhen;
    foreach(Domain *dom, domains) {
        if(dom->getName() == ui->domainTwo->currentText()) {
            unsharedPhen = dom->getPhenomena();
            break;
        }
    }

    // Create the list of unshared phenomena by removing the shared ones from
    // the list of all phenomena owned by the domain
    foreach(Phenomenon phenomenon, unsharedPhen) {        //Domain 2 Phenomena
        foreach(QString phenom, dom1SharedPhenomena) { //Currently shared
            if(phenomenon.name == phenom) {
                unsharedPhen.removeOne(phenomenon);
                shared.append(phenom); //Build the shared phonomena list
            }
        }
    }

    // Build the list for unshared phenomena
    foreach(Phenomenon phenomenon, unsharedPhen) {
        unshared.append(phenomenon.name);
    }

    edit = new EditSharedPhenomenon(false);

    connect(edit, SIGNAL(updateDomain2SharedPhenomena(QStringList)),
            this, SLOT(updateDomain2SharedPhenomena(QStringList)));

    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->setSharedPhenomena(shared);
    edit->setUnsharedPhenomena(unshared);
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT called when the dropdown for domain one has been changed to
 *         a different value
 *
 *  The main functionality of this function is to clear the shared phenomena
 *  that were relevant to the value of domain one that was changed
*******************************************************************************/
void EditInterface::domain1ConnectionChanged()
{
    QStringList list;
    dom1SharedListModel->setStringList(list);
    dom1SharedPhenomena.empty();
}


/*******************************************************************************
/*! \brief SLOT called when the dropdown for domain one has been changed to
 *         a different value
 *
 *  The main functionality of this function is to clear the shared phenomena
 *  that were relevant to the value of domain one that was changed
*******************************************************************************/
void EditInterface::domain2ConnectionChanged()
{
    QStringList list;
    dom2SharedListModel->setStringList(list);
    dom2SharedPhenomena.empty();
}
