#ifndef EDITSHAREDPHENOMENON_H
#define EDITSHAREDPHENOMENON_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class EditSharedPhenomenon;
}

class EditSharedPhenomenon : public QDialog
{
    Q_OBJECT

public:
    explicit EditSharedPhenomenon(bool first, QWidget *parent = 0);
    ~EditSharedPhenomenon();

    void setUnsharedPhenomena(const QStringList &phen);
    void setSharedPhenomena(const QStringList &phen);

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

    Ui::EditSharedPhenomenon *ui;

    bool editingFirst; //determines if editing domain 1 phenomena
};

#endif // EDITSHAREDPHENOMENON_H
