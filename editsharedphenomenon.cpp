#include "editsharedphenomenon.h"
#include "ui_editsharedphenomenon.h"

#include <qdebug.h>

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

EditSharedPhenomenon::~EditSharedPhenomenon()
{
    delete ui;
}

void EditSharedPhenomenon::setUnsharedPhenomena(QList<Phenomenon> phens)
{
    unsharedPhenomena = phens;
    QStringList phen;
    foreach (Phenomenon pheno, unsharedPhenomena) {
        phen << pheno.name;
    }
    unsharedListModel->setStringList(phen);
}

void EditSharedPhenomenon::setSharedPhenomena(QList<Phenomenon> phens)
{
    sharedPhenomena = phens;
    QStringList phen;
    foreach (Phenomenon pheno, sharedPhenomena) {
        phen << pheno.name;
    }
    sharedListModel->setStringList(phen);
}

void EditSharedPhenomenon::on_okButton_clicked()
{
    if(editingFirst && sharedListModel->stringList().size() > 0)
        emit updateDomain1SharedPhenomena(sharedListModel->stringList());
    else if(!editingFirst && sharedListModel->stringList().size() > 0)
        emit updateDomain2SharedPhenomena(sharedListModel->stringList());

    close();
}

void EditSharedPhenomenon::on_cancelButton_clicked()
{
    close();
}

void EditSharedPhenomenon::on_addButton_clicked()
{
    QString phen = unsharedListModel->index(
                ui->unsharedListView->currentIndex().row(),0 )
            .data( Qt::DisplayRole )
            .toString();

    if(phen != "") {
        QStringList sharedList = sharedListModel->stringList();
        QStringList unsharedList = unsharedListModel->stringList();

        unsharedList.removeOne(phen);
        unsharedListModel->setStringList(unsharedList);

        sharedList.append(phen);
        sharedListModel->setStringList(sharedList);
    }
}

void EditSharedPhenomenon::on_removeButton_clicked()
{
    QString phen = sharedListModel->index(
                ui->sharedListView->currentIndex().row(),0 )
            .data( Qt::DisplayRole )
            .toString();

    if(phen != "") {
        QStringList sharedList = sharedListModel->stringList();
        QStringList unsharedList = unsharedListModel->stringList();

        sharedList.removeOne(phen);
        sharedListModel->setStringList(sharedList);

        unsharedList.append(phen);
        unsharedListModel->setStringList(unsharedList);
    }
}
