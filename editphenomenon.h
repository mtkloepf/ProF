#ifndef EDITPHENOMENON_H
#define EDITPHENOMENON_H

/*******************************************************************************
/*! \class editphenomenon.h
 *
 *  A dialog that appears when editing phenomenon properties
*******************************************************************************/
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

    void setPhenonemonName(const QString name);
    void setPhenomenonType(const QString type);
    void setPhenomenonDesc(const QString desc);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();

signals:
    void updatePhenomenon(Phenomenon);

private:
    Ui::EditPhenomenon *ui;
};

#endif // EDITPHENOMENON_H
