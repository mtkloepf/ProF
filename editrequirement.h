#ifndef EDITREQUIREMENT_H
#define EDITREQUIREMENT_H

#include <QDialog>
#include <QMessageBox>
#include <QStringListModel>

#include "contextdata.h"
#include "editsharedphenomenon.h"

namespace Ui {
class EditRequirement;
}

class EditRequirement : public QDialog
{
    Q_OBJECT

public:
    explicit EditRequirement(ContextData *data, QWidget *parent = 0);
    ~EditRequirement();

    void setRequirementDescription(const QString desc);
    void setRequirementName(const QString name);
    void setRequirementType(QString type);

    void setDomainNames(const QStringList names);
    void setConnections(const Domain *first, const Domain *second);
    void setDom1SharedPhenomena(const QList<Phenomenon> phen);
    void setDom2SharedPhenomena(const QList<Phenomenon> phen);

    void editRequirement();
    void deleteRequirement();

public slots:
    void updateDomain1SharedPhenomena(QStringList phen);
    void updateDomain2SharedPhenomena(QStringList phen);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_editDom1Phen_clicked();
    void on_editDom2Phen_clicked();
    void domain1ConnectionChanged();
    void domain2ConnectionChanged();

signals:
    void updateDescription(QString);
    void updateName(QString);
    void updateType(QString);
    void updateDomains(QString, QString);
    void updateDom1SharedPhenomena(QList<Phenomenon>);
    void updateDom2SharedPhenomena(QList<Phenomenon>);

private:
    QStringListModel *dom1SharedListModel;
    QStringListModel *dom2SharedListModel;
    ContextData *context;

    QList<Phenomenon> dom1SharedPrevious;
    QList<Phenomenon> dom2SharedPrevious;

    QList<Phenomenon> dom1SharedPhenomena;
    QList<Phenomenon> dom2SharedPhenomena;

    QStringList domains;

    QMessageBox *errorMsg;

    EditSharedPhenomenon *edit;

    Ui::EditRequirement *ui;
};

#endif // EDITREQUIREMENT_H
