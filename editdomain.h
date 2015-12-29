#ifndef EDITDOMAIN_H
#define EDITDOMAIN_H

/*******************************************************************************
/*! \class editdomain.h
 *
 *  A dialog that appears when editing domain properties
*******************************************************************************/
#include <QDialog>
#include <QList>
#include <QStandardItemModel>

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
    ~EditDomain();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();

signals:
    void updateDescription(QString);
    void updateName(QString);
    void updateType(QString);

private:
    QStandardItemModel *listModel;
    bool isMachine;
    Ui::EditDomain *ui;
};

#endif // EDITDOMAIN_H
