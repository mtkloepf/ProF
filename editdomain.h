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
#include "phenomenon.h"

namespace Ui {
class EditDomain;
}

class EditDomain : public QDialog
{
    Q_OBJECT

public:
    explicit EditDomain(QWidget *parent = 0, bool machine=false);
    void setDomainDescription(QString desc);
    void setDomainName(QString name);
    void setDomainType(QString type);
    void setPhenomena(QList<Phenomenon> phen);
    //void editPhenomenon();
    ~EditDomain();

public slots:
    void phenomenonChanged(Phenomenon phen);
    void phenomenonAdded(Phenomenon phen);
    void phenomenonRemoved(Phenomenon phen);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();
    void on_addPhenomena_clicked();
    //void on_editPhenomenon_clicked();

signals:
    void updateDescription(QString);
    void updateName(QString);
    void updateType(QString);
    void editPhenomenon(Phenomenon);
    void addPhenomenon(Phenomenon);

private:
    QStringListModel *listModel;
    bool isMachine;
    Ui::EditDomain *ui;

    EditPhenomenon *edit;
};

#endif // EDITDOMAIN_H
