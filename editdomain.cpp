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

    //Turn off editing of phenomena names
    ui->phenomenaListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create a model for the phenomena list view and set the prototype
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
    int i;
    for(i = 0; i < list.size(); i++) {
        if(list.at(i) == name) {
            list.replace((i), phen.name);
            phenomena.replace(i, phen);
            listModel->setStringList(list);
            exists = true;
            break;
        }
        if(list.at(i) == phen.name) {
            exists = true;
            break;
        }
    }
    if(!exists) {
        list << phen.name;
        listModel->setStringList(list);
        phenomena.append(phen);
    }
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

void EditDomain::setPhenomena(QList<Phenomenon> phen)
{
    phenomena = phen;
    QStringList pheno;
    foreach (Phenomenon phenomenon, phenomena) {
        pheno << phenomenon.name;
    }
    listModel->setStringList(pheno);
}

/*******************************************************************************
/*! \brief Slot called when the OK button of this dialog is clicked
 *
 *  This function is used to send all data currently in the form to the domain
*******************************************************************************/
void EditDomain::on_okButton_clicked()
{
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
/*! \brief Slot called when the Cancel button of this dialog is clicked
 *
 *  Exits the domain editing dialog.
 *  If called, NO data will be saved to the domain
*******************************************************************************/
void EditDomain::on_cancelButton_clicked()
{
    close();
}

/*******************************************************************************
/*! \brief Slot called when the Reset button of this dialog is clicked
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
}

void EditDomain::on_addPhenomenon_clicked()
{
    edit = new EditPhenomenon();

    connect(edit, SIGNAL(updatePhenomenon(Phenomenon)),
            this, SLOT(phenomenonUpdated(Phenomenon)));

    edit->show();
    edit->raise();
    edit->activateWindow();
}

void EditDomain::on_editPhenomenon_clicked()
{
    edit = new EditPhenomenon();

    //Get the name of the phenomenon that's selected in the list view
    QString name = listModel->index( ui->phenomenaListView->currentIndex().row(),
                                     0 ).data( Qt::DisplayRole ).toString();
    this->name = name;
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

    edit->show();
    edit->raise();
    edit->activateWindow();
}

void EditDomain::on_deletePhenomenon_clicked()
{
    QString name = listModel->index( ui->phenomenaListView->currentIndex().row(),
                                     0 ).data( Qt::DisplayRole ).toString();
    listModel->removeRow(ui->phenomenaListView->currentIndex().row());
    foreach(Phenomenon phenomenon, phenomena) {
        if(phenomenon.name == name) {
            phenomena.removeOne(phenomenon);
            break;
        }
    }
}
