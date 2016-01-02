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
    QList<Phenomenon> phenomena();
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
void EditDomain::phenomenonAdded(Phenomenon phen)
{
    bool exists = false;
    QStringList list = listModel->stringList();
    foreach(QString str, list) {
        if(str.compare(phen.name) == 0) {
            exists = true;
        }
    }
    if(!exists) {
        list << phen.name;
        listModel->setStringList(list);
        phenomena.append(phen);
    }
    else {
        qDebug() << "Phenomenon already exists in the list";
    }
}

void EditDomain::phenomenonRemoved(Phenomenon phen)
{

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
    QStringList phenomena;
    foreach (Phenomenon phenomenon, phen) {
        phenomena << phenomenon.name;
    }
    listModel->setStringList(phenomena);
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
 *  Resets all data in the form to NULL. Resets form to default domain values
*******************************************************************************/
void EditDomain::on_resetButton_clicked()
{
    ui->nameLineEdit->clear();
    ui->descriptionTextEdit->clear();
}

void EditDomain::on_addPhenomena_clicked()
{
    edit = new EditPhenomenon();

    connect(edit, SIGNAL(addPhenomenon(Phenomenon)),
            this, SLOT(phenomenonAdded(Phenomenon)));

    edit->show();
    edit->raise();
    edit->activateWindow();


    //connect(edit, SIGNAL(editPhenomenon(Phenomenon)),
    //        this, SIGNAL(editPhenomenon(Phenomenon)));
}
