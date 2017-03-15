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
    explicit EditDomain(QString &name, QString &desc,
                        QString &type, QList<Phenomenon> &phen,
                        QWidget *parent = 0);
    ~EditDomain();

private:
    void setDomainDescription(QString &desc);
    void setDomainName(QString &name);
    void setDomainType(QString &type);
    void setPhenomena(const QList<Phenomenon> &phen);

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
    void updatePhenomena(QList<Phenomenon>);

private:
    QStringListModel *listModel;

    QList<Phenomenon> &phenomena;
    QString selectedPhenName;
    QString &domainName;
    QString &domainDesc;
    QString &domainType;

    Ui::EditDomain *ui;

    EditPhenomenon *edit;
};

#endif // EDITDOMAIN_H
