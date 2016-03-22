#ifndef EDITSHAREDPHENOMENON_H
#define EDITSHAREDPHENOMENON_H

#include <QDialog>
#include <QStringListModel>

#include "phenomenon.h"

namespace Ui {
class EditSharedPhenomenon;
}

class EditSharedPhenomenon : public QDialog
{
    Q_OBJECT

public:
    explicit EditSharedPhenomenon(bool first, QWidget *parent = 0);
    ~EditSharedPhenomenon();

    void setUnsharedPhenomena(QList<Phenomenon> phen);
    void setSharedPhenomena(QList<Phenomenon> phen);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();

signals:
    void updateDomain1SharedPhenomena(QStringList phen);
    void updateDomain2SharedPhenomena(QStringList phen);

private:
    QStringListModel *unsharedListModel;
    QStringListModel *sharedListModel;

    QList<Phenomenon> unsharedPhenomena;
    QList<Phenomenon> sharedPhenomena;

    Ui::EditSharedPhenomenon *ui;

    bool editingFirst; //determines if editing domain 1 phenomena
};

#endif // EDITSHAREDPHENOMENON_H
