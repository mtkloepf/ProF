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

/*******************************************************************************
/*! \brief Constructor
 *
 * @param parent widget that parents this dialog
*******************************************************************************/
EditDomain::EditDomain(QWidget *parent, bool machine) :
    QDialog(parent),
    ui(new Ui::EditDomain),
    isMachine(machine)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(geometry().width(), geometry().height());

    //Special logic for the machine domain. Cannot edit the type for machine
    //domain
    if(isMachine) {
        ui->givenRadio->setEnabled(false);
        ui->designedRadio->setEnabled(false);
    } else ui->machineRadio->setEnabled(false);

    //Turn off editing of phenomena names directly through the list view
    ui->phenomenaListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create a model for the phenomena list view
    listModel = new QStringListModel();
    ui->phenomenaListView->setModel(listModel);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
EditDomain::~EditDomain()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Sends the text of the description text edit to the domain once OK is
 *         clicked
 *
 * @param desc the text held in the text edit
*******************************************************************************/
void EditDomain::setDomainDescription(QString desc)
{
    ui->descriptionTextEdit->setText(desc);
}

/*******************************************************************************
/*! \brief Sends the text of the name line edit to the domain once OK is
 *         clicked
 *
 * @param name the text held in the name line edit
*******************************************************************************/
void EditDomain::setDomainName(QString name)
{
    ui->nameLineEdit->setText(name);
}

/*******************************************************************************
/*! \brief Sends the status of the radio buttons defining domain type
 *
 * @param type the text of whichever radio button is checked
*******************************************************************************/
void EditDomain::setDomainType(QString type)
{
    if(type == "Designed")
        ui->designedRadio->setChecked(true);
    else if(type == "Given")
        ui->givenRadio->setChecked(true);
    else
        ui->machineRadio->setChecked(true);
}

/*******************************************************************************
/*! \brief Sets the list of phenomena to show all phenomena attached to
 *         the domain
 *
 * @param phen a list of phenomena to populate the list with
*******************************************************************************/
void EditDomain::setPhenomena(QList<Phenomenon> phen)
{
    phenomena = phen;
    QStringList pheno;
    foreach (Phenomenon phenomenon, phenomena) {
        pheno << phenomenon.name;
    }
    listModel->setStringList(pheno);

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
 * SLOT FUNCTIONS
/******************************************************************************/

/*******************************************************************************
/*! \brief Called when a phenomenon has been added through the add phenomenon
 *         button. Duplicates are not allowed. Adds the new phenomenon to the
 *         list to be displayed in the list.
 *
 * @param phen a phenomenon object that holds the information for the newly
 *             created phenomenon. Used to put the name into the list of
 *             phenomena
*******************************************************************************/
void EditDomain::phenomenonUpdated(Phenomenon phen)
{
    bool exists = false;
    QStringList list = listModel->stringList();

    //Check to see if the phenomenon already exists and update it
    for(int i = 0; i < list.size(); i++) {
        if(list.at(i) == name) {
            //If the new name is an empty string, we just delete the phenomenon
            if(phen.name == "") {
                phenomena.removeAt(i);
                list.removeAt(i);
            }

            //Otherwise update the name in the in the list
            else {
                list.replace((i), phen.name);
                phenomena.replace(i, phen);
            }
            listModel->setStringList(list);
            exists = true;
            break;
        }

        //Duplicates are not allowed
        if(list.at(i) == phen.name) {
            exists = true;
            break;
        }
    }

    //If the phenomenon does not exist after searching, add it
    if(!exists) {
        list << phen.name;
        listModel->setStringList(list);
        phenomena.append(phen);
    }
}

/*******************************************************************************
/*! \brief SLOT called when the OK button of this dialog is clicked
 *
 *  This function is used to send all data currently in the form to the domain
*******************************************************************************/
void EditDomain::on_okButton_clicked()
{
    //Emit signals to update the domain attributes before closing the window
    emit updateName(ui->nameLineEdit->text());
    emit updateDescription(ui->descriptionTextEdit->toPlainText());
    if(ui->designedRadio->isChecked())
        emit updateType("Designed");
    else
        emit updateType("Given");
    emit updatePhenomena(phenomena);
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
    this->name = name;

    edit = new EditPhenomenon(this);

    //Set all the phenomenon attributes for editing
    foreach(Phenomenon pheno, phenomena) {
        if(pheno.name == name) {
            edit->setPhenonemonName(name);
            edit->setPhenomenonDesc(pheno.description);
            edit->setPhenomenonType(pheno.type);
            break;
        }
    }

    connect(edit, SIGNAL(updatePhenomenon(Phenomenon)),
            this, SLOT(phenomenonUpdated(Phenomenon)));

    edit->exec();

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
    //Enable the delete and edit buttons when the list has something in it
    else {
        ui->deletePhenomenon->setEnabled(true);
        ui->editPhenomenon->setEnabled(true);
    }

    //Remove the phenomenon from the phenomena owned by the domain
    foreach(Phenomenon phenomenon, phenomena) {
        if(phenomenon.name == name) {
            phenomena.removeOne(phenomenon);
            break;
        }
    }
}
