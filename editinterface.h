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

#include "editphenomenon.h"
#include "phenomenon.h"

namespace Ui {
class EditInterface;
}

class EditInterface : public QDialog
{
    Q_OBJECT

public:
    explicit EditInterface(QWidget *parent = 0);

    void setInterfaceDescription(const QString desc);
    void setInterfaceName(const QString name);
    void setDomainNames(const QStringList names);
    void setConnections(const QString first, const QString second);
    ~EditInterface();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();

signals:
    void updateDescription(QString);
    void updateName(QString);
    void updateDomains(QString first, QString second);

private:
    QStringListModel *listModel;
    QList<Phenomenon> phenomena;
    QStringList domains;
    QMessageBox *errorMsg;

    Ui::EditInterface *ui;
};

#endif // EDITINTERFACE_H
