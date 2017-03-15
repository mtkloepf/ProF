/*******************************************************************************
/*! \class editdomain.cpp
 *
 *  Dialog used for editing domain properties. The fields of the dialog are
 *  initially populated from the domain creating this dialog. Once the OK
 *  button is clicked, this dialog sends the changes to the domain to update
 *  data
*******************************************************************************/
#include "editdomain.h"
#include "ui_editdomain.h"

#include <QDebug>
/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent widget that parents this dialog
*******************************************************************************/
EditDomain::EditDomain(QString &name, QString &desc, QString &type,
                       QList<Phenomenon> &phen, QWidget *parent) :
    QDialog(parent),
    domainName(name),
    domainDesc(desc),
    domainType(type),
    phenomena(phen),
    ui(new Ui::EditDomain)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(geometry().width(), geometry().height());

    //Turn off editing of phenomena names directly through the list view
    ui->phenomenaListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create a model for the phenomena list view
    listModel = new QStringListModel();
    ui->phenomenaListView->setModel(listModel);

    ui->nameLineEdit->setText(domainName);
    ui->descriptionTextEdit->setText(domainDesc);

    //Used to set the correct radio button for type and populating
    //the phenomena list
    setDomainType(domainType);
    setPhenomena(phenomena);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
EditDomain::~EditDomain()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Sends the status of the radio buttons defining domain type
 *
 * @param type the text of whichever radio button is checked
*******************************************************************************/
void EditDomain::setDomainType(QString &type)
{
    if(type == "Designed") {
        ui->machineRadio->setEnabled(false);
        ui->designedRadio->setChecked(true);
    }
    else if(type == "Given") {
        ui->machineRadio->setEnabled(false);
        ui->givenRadio->setChecked(true);
    }
    else {
        ui->givenRadio->setEnabled(false);
        ui->designedRadio->setEnabled(false);
        ui->machineRadio->setChecked(true);
    }
}

/*******************************************************************************
/*! \brief Sets the list of phenomena to show all phenomena attached to
 *         the domain
 *
 * @param phen a list of phenomena to populate the list with
*******************************************************************************/
void EditDomain::setPhenomena(const QList<Phenomenon> &phen)
{
    QStringList phenList;
    foreach (Phenomenon phenomenon, phen) {
        phenList << phenomenon.getName();
    }
    listModel->setStringList(phenList);
    phenomena = phen;

    if(phenomena.size() > 0) {
        ui->editPhenomenon->setEnabled(true);
        ui->deletePhenomenon->setEnabled(true);
    }
}


/*******************************************************************************
 * SLOT FUNCTIONS
/******************************************************************************/

/*******************************************************************************
/*! \brief SLOT Called when a phenomenon has been added through the add phenomenon
 *         button or updated through the edit button. Duplicates are not allowed.
 *         Adds the new phenomenon to the list to be displayed in the list.
 *
 * @param phen a phenomenon object that holds the information for the newly
 *             created phenomenon.
*******************************************************************************/
void EditDomain::phenomenonUpdated(Phenomenon phen)
{
    bool exists = false;
    QStringList list = listModel->stringList();

    //Check to see if the phenomenon already exists and update it
    for(int i = 0; i < list.size(); i++) {
        if(list.at(i) == selectedPhenName) {
            //If the new name is an empty string, we just delete the phenomenon
            if(phen.getName() == "") {
                phenomena.removeAt(i);
                list.removeAt(i);
            }

            //Otherwise update the name in the in the list
            else {
                list.replace((i), phen.getName());
                phenomena.replace(i, phen);
            }
            listModel->setStringList(list);
            exists = true;
            break;
        }

        //Duplicates are not allowed
        if(list.at(i) == phen.getName()) {
            exists = true;
            break;
        }
    }

    //If the phenomenon does not exist after searching, add it
    if(!exists) {
        list << phen.getName();
        listModel->setStringList(list);
        phenomena.append(phen);
    }

    if(listModel->rowCount() == 0) {
        ui->deletePhenomenon->setEnabled(false);
        ui->editPhenomenon->setEnabled(false);
    }
    //Enable the delete and edit buttons when the list has something in it
    else {
        ui->deletePhenomenon->setEnabled(true);
        ui->editPhenomenon->setEnabled(true);
    }
}

/*******************************************************************************
/*! \brief SLOT called when the OK button of this dialog is clicked
 *
 *  This function is used to send all data currently in the form to the domain
*******************************************************************************/
void EditDomain::on_okButton_clicked()
{
    //Set all the values onto the domain being edited before exiting
    //Note: The local data variables are set to references of the domain data
    domainName = ui->nameLineEdit->text();
    domainDesc = ui->descriptionTextEdit->toPlainText();
    if(ui->designedRadio->isChecked())
        domainType = "Designed";
    else if(ui->givenRadio->isChecked())
        domainType = "Given";
    else
        domainType = "Machine";
    close();
}

/*******************************************************************************
/*! \brief SLOT called when the Cancel button of this dialog is clicked
 *
 *  Exits the domain editing dialog.
 *  If called, NO data will be saved to the domain
*******************************************************************************/
void EditDomain::on_cancelButton_clicked()
{
    close();
}

/*******************************************************************************
/*! \brief SLOT called when the Reset button of this dialog is clicked
 *
 *  Resets form to default domain values
*******************************************************************************/
void EditDomain::on_resetButton_clicked()
{
    ui->nameLineEdit->clear();
    ui->descriptionTextEdit->clear();
    phenomena.clear();
    QStringList list;
    listModel->setStringList(list);

    //Disable the delete and edit buttons when the list is empty
    if(listModel->rowCount() == 0) {
        ui->deletePhenomenon->setEnabled(false);
        ui->editPhenomenon->setEnabled(false);
    }
    //Enable the delete and edit buttons when the list has something in it
    else {
        ui->deletePhenomenon->setEnabled(true);
        ui->editPhenomenon->setEnabled(true);
    }
}

/*******************************************************************************
/*! \brief SLOT called when the add phenomenon button is clicked
 *
 *  Opens a new dialog to add a new phenomenon to the domain
*******************************************************************************/
void EditDomain::on_addPhenomenon_clicked()
{
    edit = new EditPhenomenon(this);

    connect(edit, SIGNAL(updatePhenomenon(Phenomenon)),
            this, SLOT(phenomenonUpdated(Phenomenon)));

    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT called when the edit phenomenon button is clicked
 *
 *  Opens a new dialog to edit the currently selected phenomenon
*******************************************************************************/
void EditDomain::on_editPhenomenon_clicked()
{
    //Check the number of items in the view. If there are none, return
    if(listModel->rowCount() == 0) return;

    //Get the name of the phenomenon that's selected in the list view
    QString name = listModel->index( ui->phenomenaListView->currentIndex().row(),
                                     0 ).data( Qt::DisplayRole ).toString();

    //If there is no selection, return. We don't want empty names for phenomena
    if(name == "") return;
    this->selectedPhenName = name;

    edit = new EditPhenomenon(this);

    //Set all the phenomenon attributes for editing
    foreach(Phenomenon pheno, phenomena) {
        if(pheno.getName() == name) {
            edit->setPhenonemonName(name);
            edit->setPhenomenonDesc(pheno.getDescription());
            edit->setPhenomenonType(pheno.getType());
            break;
        }
    }

    connect(edit, SIGNAL(updatePhenomenon(Phenomenon &)),
            this, SLOT(phenomenonUpdated(Phenomenon &)));

    edit->setAttribute(Qt::WA_DeleteOnClose);
    edit->exec();
}

/*******************************************************************************
/*! \brief SLOT called when the delete phenomenon button is clicked
 *
 *  Deletes the currently selected phenomenon in the list
*******************************************************************************/
void EditDomain::on_deletePhenomenon_clicked()
{
    //Get the name of the currently selected phenomenon
    QString name = listModel->index( ui->phenomenaListView->currentIndex().row(),
                                     0 ).data( Qt::DisplayRole ).toString();
    //Remove the phenomenon from the list view
    listModel->removeRow(ui->phenomenaListView->currentIndex().row());

    //Disable the delete and edit buttons when the list is empty
    if(listModel->rowCount() == 0) {
        ui->deletePhenomenon->setEnabled(false);
        ui->editPhenomenon->setEnabled(false);
    }

    //Remove the phenomenon from the phenomena owned by the domain
    foreach(Phenomenon phenomenon, phenomena) {
        if(phenomenon.getName() == name) {
            phenomena.removeOne(phenomenon);
            break;
        }
    }
}
