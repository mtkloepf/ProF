#ifndef EDITDOMAIN_H
#define EDITDOMAIN_H

/*******************************************************************************
/*! \class editdomain.h
 *
 *  A dialog that appears when editing domain properties
*******************************************************************************/
#include <QDialog>
#include <QList>
#include <QStringListModel>

#include "editphenomenon.h"

namespace Ui {
class EditDomain;
}

class EditDomain : public QDialog
{
    Q_OBJECT

public:
    explicit EditDomain(QWidget *parent = 0);
    ~EditDomain();

    void setDomainDescription(QString desc);
    void setDomainName(QString name);
    void setDomainType(QString type);
    void setPhenomena(QList<Phenomenon> phen);

public slots:
    void phenomenonUpdated(Phenomenon phen);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();
    void on_addPhenomenon_clicked();
    void on_editPhenomenon_clicked();
    void on_deletePhenomenon_clicked();

signals:
    void updateDescription(QString);
    void updateName(QString);
    void updateDomainType(QString);

    //Update the phenomena of the domain when done editing
    void updatePhenomena(QList<Phenomenon>);

private:
    QStringListModel *listModel;

    QList<Phenomenon> phenomena;

    QString name;

    Ui::EditDomain *ui;

    EditPhenomenon *edit;
};

#endif // EDITDOMAIN_H
