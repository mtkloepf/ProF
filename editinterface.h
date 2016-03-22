#ifndef EDITINTERFACE_H
#define EDITINTERFACE_H

/*******************************************************************************
/*! \class editinterface.h
 *
 *  A dialog that appears when editing interface properties
*******************************************************************************/
#include <QDialog>
#include <QMessageBox>
#include <QStringListModel>

#include "contextdata.h"
#include "editsharedphenomenon.h"

namespace Ui {
class EditInterface;
}

class EditInterface : public QDialog
{
    Q_OBJECT

public:
    explicit EditInterface(ContextData *data, QWidget *parent = 0);
    ~EditInterface();

    void setInterfaceDescription(const QString desc);
    void setInterfaceName(const QString name);
    void setDomainNames(const QStringList names);
    void setConnections(const Domain *first, const Domain *second);
    void setDom1SharedPhenomena(const QList<Phenomenon> phen);
    void setDom2SharedPhenomena(const QList<Phenomenon> phen);

public slots:
    void updateDomain1SharedPhenomena(QStringList phen);
    void updateDomain2SharedPhenomena(QStringList phen);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();
    void on_editDom1Phen_clicked();
    void on_editDom2Phen_clicked();
    void domain1ConnectionChanged();
    void domain2ConnectionChanged();

signals:
    void updateDescription(QString);
    void updateName(QString);
    void updateDomains(QString, QString);
    void updateDom1SharedPhenomena(QList<Phenomenon>);
    void updateDom2SharedPhenomena(QList<Phenomenon>);

private:
    QStringListModel *dom1SharedListModel;
    QStringListModel *dom2SharedListModel;
    ContextData *data;

    QList<Phenomenon> dom1SharedPrevious;
    QList<Phenomenon> dom2SharedPrevious;

    QList<Phenomenon> dom1SharedPhenomena;
    QList<Phenomenon> dom2SharedPhenomena;

    QStringList domains;

    QMessageBox *errorMsg;

    Ui::EditInterface *ui;

    EditSharedPhenomenon *edit;
};

#endif // EDITINTERFACE_H
