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
            ui->domainOne->setCurrentIndex(ui->domainOne->findText(first->getName()));
    else if(first == NULL)
        ui->domainOne->setCurrentIndex(ui->domainOne->findText("None"));
    if(second != NULL)
        if(ui->domainTwo->findText(second->getName()) != -1)
            ui->domainTwo->setCurrentIndex(ui->domainTwo->findText(second->getName()));
    else if(second == NULL)
        ui->domainTwo->setCurrentIndex(ui->domainTwo->findText("None"));
}

void EditInterface::setDom1SharedPhenomena(const QList<Phenomenon> phen)
{
    /*dom1SharedPhenomena = phen;
    QStringList pheno;
    foreach (Phenomenon phenomenon, dom1SharedPhenomena) {
        pheno << phenomenon.name;
    }
    dom1SharedListModel->setStringList(pheno);
    dom1SharedPrevious = dom1SharedPhenomena;*/
}

void EditInterface::setDom2SharedPhenomena(const QList<Phenomenon> phen)
{
    /*dom2SharedPhenomena = phen;
    QStringList pheno;
    foreach (Phenomenon phenomenon, dom2SharedPhenomena) {
        pheno << phenomenon.name;
    }
    dom2SharedListModel->setStringList(pheno);
    dom2SharedPrevious = dom2SharedPhenomena;*/
}

void EditInterface::updateDomain1SharedPhenomena(QStringList phen)
{
    /*QList<Phenomenon> phenomena =
            data->findDomain(ui->domainOne->currentText())->getPhenomena();

    dom1SharedListModel->setStringList(phen);

    // Clear the list of shared phenomena so we can rebuild it
    dom1SharedPhenomena.clear();
    foreach(Phenomenon phenomenon, phenomena) {
        foreach(QString name, phen) {
            if(phenomenon.name == name) {
                dom1SharedPhenomena.append(phenomenon);
            }
        }
    }*/
}

void EditInterface::updateDomain2SharedPhenomena(QStringList phen)
{
    /*QList<Phenomenon> phenomena =
            data->findDomain(ui->domainTwo->currentText())->getPhenomena();

    dom2SharedListModel->setStringList(phen);

    // Clear the list of shared phenomena so we can rebuild it
    dom2SharedPhenomena.clear();
    foreach(Phenomenon phenomenon, phenomena) {
        foreach(QString name, phen) {
            if(phenomenon.name == name) {
                dom2SharedPhenomena.append(phenomenon);
            }
        }
    }*/
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

void EditInterface::on_editDom1Phen_clicked()
{
    /*QList<Phenomenon> phen;
    foreach(Domain *dom, data->getDomains()) {
        if(dom->getName() == ui->domainOne->currentText()) {
            phen = dom->getPhenomena();
            break;
        }
    }

    // Create the list of unshared phenomena by removing the shared ones from
    // the list of all phenomena owned by the domain
    foreach(Phenomenon phenomenon, phen) {
        foreach(Phenomenon phenom, dom1SharedPhenomena) {
            if(phenomenon.name == phenom.name) {
                phen.removeOne(phenomenon);
            }
        }
    }

    edit = new EditSharedPhenomenon(true);

    connect(edit, SIGNAL(updateDomain1SharedPhenomena(QStringList)),
            this, SLOT(updateDomain1SharedPhenomena(QStringList)));

    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->setSharedPhenomena(dom1SharedPhenomena);
    edit->setUnsharedPhenomena(phen);
    edit->exec();*/
}

void EditInterface::on_editDom2Phen_clicked()
{
   /* QList<Phenomenon> phen;
    foreach(Domain *dom, data->getDomains()) {
        if(dom->getName() == ui->domainTwo->currentText()) {
            phen = dom->getPhenomena();
            break;
        }
    }

    // Create the list of unshared phenomena by removing the shared ones from
    // the list of all phenomena owned by the domain
    foreach(Phenomenon phenomenon, phen) {
        foreach(Phenomenon phenom, dom1SharedPhenomena) {
            if(phenomenon.name == phenom.name) {
                phen.removeOne(phenomenon);
            }
        }
    }

    edit = new EditSharedPhenomenon(false);

    connect(edit, SIGNAL(updateDomain2SharedPhenomena(QStringList)),
            this, SLOT(updateDomain2SharedPhenomena(QStringList)));

    edit->setAttribute( Qt::WA_DeleteOnClose );
    edit->setSharedPhenomena(dom2SharedPhenomena);
    edit->setUnsharedPhenomena(phen);
    edit->exec();*/
}

void EditInterface::domain1ConnectionChanged()
{
    QStringList list;
    dom1SharedListModel->setStringList(list);
    dom1SharedPhenomena.empty();
}

void EditInterface::domain2ConnectionChanged()
{
    QStringList list;
    dom2SharedListModel->setStringList(list);
    dom2SharedPhenomena.empty();
}
