#ifndef EDITPHENOMENON_H
#define EDITPHENOMENON_H

#include <QDialog>

#include "phenomenon.h"

namespace Ui {
class EditPhenomenon;
}

class EditPhenomenon : public QDialog
{
    Q_OBJECT

public:
    explicit EditPhenomenon(QWidget *parent = 0);
    ~EditPhenomenon();

    void setPhenonemonName(QString name);
    void setPhenomenonType(QString type);
    void setPhenomenonDesc(QString desc);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();

signals:
    void addPhenomenon(Phenomenon);

private:
    Ui::EditPhenomenon *ui;
};

#endif // EDITPHENOMENON_H
