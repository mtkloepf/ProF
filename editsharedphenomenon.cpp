#include "editsharedphenomenon.h"
#include "ui_editsharedphenomenon.h"

/*******************************************************************************
/*! \brief Constructor
 *
 * @param first  determines if the domain being used is domain one or two
 * @param parent widget that parents this dialog
*******************************************************************************/
EditSharedPhenomenon::EditSharedPhenomenon(bool first, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSharedPhenomenon),
    editingFirst(first)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(geometry().width(), geometry().height());

    //Turn off editing of phenomena names directly through the list view
    ui->unsharedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sharedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create a model for the phenomena list view and set the prototype
    unsharedListModel = new QStringListModel();
    sharedListModel = new QStringListModel();
    ui->unsharedListView->setModel(unsharedListModel);
    ui->sharedListView->setModel(sharedListModel);
}

/*******************************************************************************
/*! \brief Default Destructor
*******************************************************************************/
EditSharedPhenomenon::~EditSharedPhenomenon()
{
    delete ui;
}

/*******************************************************************************
/*! \brief Update the list of unshared phenomena in the dialog
 *
 * @param phens the new list
*******************************************************************************/
void EditSharedPhenomenon::setUnsharedPhenomena(const QStringList &phens)
{
    unsharedListModel->setStringList(phens);
}

/*******************************************************************************
/*! \brief Update the list of shared phenomena in the dialog
 *
 * @param phens the new list
*******************************************************************************/
void EditSharedPhenomenon::setSharedPhenomena(const QStringList &phens)
{
    sharedListModel->setStringList(phens);
}

/*******************************************************************************
/*! \brief SLOT called when done editing shared phenomena for a domain
 *
 *  Sends the relevant list of shared phenomena back to the interface dialog
*******************************************************************************/
void EditSharedPhenomenon::on_okButton_clicked()
{
    if(editingFirst)
        emit updateDomain1SharedPhenomena(sharedListModel->stringList());
    else if(!editingFirst)
        emit updateDomain2SharedPhenomena(sharedListModel->stringList());

    close();
}

/*******************************************************************************
/*! \brief SLOT called when the cancel button is clicked
 *
 *  Closes the dialog and does not save ANY of the editing done to shared
 *  phenomena
*******************************************************************************/
void EditSharedPhenomenon::on_cancelButton_clicked()
{
    close();
}

/*******************************************************************************
/*! \brief SLOT called when the >> button is clicked
 *
 *  >> is the text for the button that adds the currently selected unshared
 *  phenomenon to the shared phenomena list, removing it from unshared
*******************************************************************************/
void EditSharedPhenomenon::on_addButton_clicked()
{
    //Grabs the name of the currently selected phenomenon
    QString phen = unsharedListModel->index(
                ui->unsharedListView->currentIndex().row(),0 )
            .data( Qt::DisplayRole )
            .toString();

    //If the selected phenomenon is not an empty string and there IS a selection
    if(phen != "") {
        QStringList sharedList = sharedListModel->stringList();
        QStringList unsharedList = unsharedListModel->stringList();

        unsharedList.removeOne(phen);
        unsharedListModel->setStringList(unsharedList);

        sharedList.append(phen);
        sharedListModel->setStringList(sharedList);
    }
}

/*******************************************************************************
/*! \brief SLOT called when the << button is clicked
 *
 *  << is the text for the button that removes the currently selected shared
 *  phenomenon. This moves it to the unshared phenomena list.
*******************************************************************************/
void EditSharedPhenomenon::on_removeButton_clicked()
{
    //Grabs the name of the currently selected phenomenon
    QString phen = sharedListModel->index(
                ui->sharedListView->currentIndex().row(),0 )
            .data( Qt::DisplayRole )
            .toString();

    //If the selected phenomenon is not an empty string and there IS a selection
    if(phen != "") {
        QStringList sharedList = sharedListModel->stringList();
        QStringList unsharedList = unsharedListModel->stringList();

        sharedList.removeOne(phen);
        sharedListModel->setStringList(sharedList);

        unsharedList.append(phen);
        unsharedListModel->setStringList(unsharedList);
    }
}
