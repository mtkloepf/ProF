#include "editrequirement.h"
#include "ui_editrequirement.h"

#include <qdebug.h>

EditRequirement::EditRequirement(ContextData *data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRequirement),
    context(data)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //ui->withArrowRadio->setVisible(false);
    //ui->withoutArrowRadio->setVisible(false);
    setFixedSize(geometry().width(), geometry().height());

    //Create the error message box for having duplicate connections
    errorMsg = new QMessageBox();
    errorMsg->setAttribute(Qt::WA_DeleteOnClose);

    //Turn off editing of phenomena names directly through the list view
    ui->domain1SharedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->domain2SharedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Add a "no connection" option for the combo boxes if it doesn't exist
    if(!domains.contains("None"))
        domains.append("None");

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

EditRequirement::~EditRequirement()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Sends the text of the description text edit to the interface once OK
 *         is clicked
 *
 * @param desc the text held in the text edit
*******************************************************************************/
void EditRequirement::setRequirementDescription(const QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

/*******************************************************************************
/*! \brief Sends the text of the name line edit to the interface once OK is
 *         clicked
 *
 * @param name the text held in the name line edit
*******************************************************************************/
void EditRequirement::setRequirementName(const QString name)
{
    ui->nameLineEdit->setText(name);
}

void EditRequirement::setRequirementType(QString type)
{
    if(type == "Requirement")
        ui->requirementRadio->setChecked(true);
    else if(type == "Indicative Property")
        ui->indicativeRadio->setChecked(true);
}

/*******************************************************************************
/*! \brief Used to populate the list of domains to choose as connections
 *
 * @param names the list of domains that can be chosen as connections
*******************************************************************************/
void EditRequirement::setDomainNames(const QStringList names)
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
void EditRequirement::setConnections(const Domain *first, const Domain *second)
{
    //TODO: ERRORS HAPPEN HERE WITH FIRST EDITING FIRST REQUIREMENT (SEGFAULT)
    if(first != NULL)
    {
        if(ui->domainOne->findText(first->getName()) != -1)
            ui->domainOne->setCurrentIndex(ui->domainOne->findText(first->getName()));
    }
    else if(first == NULL) {
        ui->domainOne->setCurrentIndex(ui->domainOne->findText("None"));
    }
    if(second != NULL) {
        if(ui->domainTwo->findText(second->getName()) != -1)
            ui->domainTwo->setCurrentIndex(ui->domainTwo->findText(second->getName()));
    }
    else if(second == NULL) {
        ui->domainTwo->setCurrentIndex(ui->domainTwo->findText("None"));
    }
}

void EditRequirement::setDom1SharedPhenomena(const QList<Phenomenon> phen)
{
    dom1SharedPhenomena = phen;
    QStringList pheno;
    foreach (Phenomenon phenomenon, dom1SharedPhenomena) {
        pheno << phenomenon.name;
    }
    dom1SharedListModel->setStringList(pheno);
    dom1SharedPrevious = dom1SharedPhenomena;
}

void EditRequirement::setDom2SharedPhenomena(const QList<Phenomenon> phen)
{
    dom2SharedPhenomena = phen;
    QStringList pheno;
    foreach (Phenomenon phenomenon, dom2SharedPhenomena) {
        pheno << phenomenon.name;
    }
    dom2SharedListModel->setStringList(pheno);
    dom2SharedPrevious = dom2SharedPhenomena;
}

void EditRequirement::updateDomain1SharedPhenomena(QStringList phen)
{
    QList<Phenomenon> phenomena =
            context->findDomain(ui->domainOne->currentText())->getPhenomena();

    dom1SharedListModel->setStringList(phen);

    // Clear the list of shared phenomena so we can rebuild it
    dom1SharedPhenomena.clear();
    foreach(Phenomenon phenomenon, phenomena) {
        foreach(QString name, phen) {
            if(phenomenon.name == name) {
                dom1SharedPhenomena.append(phenomenon);
            }
        }
    }
}

void EditRequirement::updateDomain2SharedPhenomena(QStringList phen)
{
    QList<Phenomenon> phenomena =
            context->findDomain(ui->domainTwo->currentText())->getPhenomena();

    dom2SharedListModel->setStringList(phen);

    // Clear the list of shared phenomena so we can rebuild it
    dom2SharedPhenomena.clear();
    foreach(Phenomenon phenomenon, phenomena) {
        foreach(QString name, phen) {
            if(phenomenon.name == name) {
                dom2SharedPhenomena.append(phenomenon);
            }
        }
    }
}

/*******************************************************************************
/*! \brief SLOT called when the OK button of this dialog is clicked
 *
 *  This function is used to send all data currently in the form to the
 *  interface
*******************************************************************************/
void EditRequirement::on_okButton_clicked()
{
    emit updateName(ui->nameLineEdit->text());
    emit updateDescription(ui->descriptionTextEdit->toPlainText());
    if(ui->requirementRadio->isChecked()) emit updateType("Requirement");
    else emit updateType("Indicative Property");

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
void EditRequirement::on_cancelButton_clicked()
{
    close();
}

void EditRequirement::on_editDom1Phen_clicked()
{
    QList<Phenomenon> phen;
    foreach(Domain *dom, context->getDomains()) {
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
//    edit->setSharedPhenomena(dom1SharedPhenomena);
//    edit->setUnsharedPhenomena(phen);
    edit->exec();
}

void EditRequirement::on_editDom2Phen_clicked()
{
    QList<Phenomenon> phen;
    foreach(Domain *dom, context->getDomains()) {
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
//    edit->setSharedPhenomena(dom2SharedPhenomena);
//    edit->setUnsharedPhenomena(phen);
    edit->exec();
}

void EditRequirement::domain1ConnectionChanged()
{
    QStringList list;
    dom1SharedListModel->setStringList(list);
    dom1SharedPhenomena.empty();
}

void EditRequirement::domain2ConnectionChanged()
{
    QStringList list;
    dom2SharedListModel->setStringList(list);
    dom2SharedPhenomena.empty();
}
