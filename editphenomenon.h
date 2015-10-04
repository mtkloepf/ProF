#ifndef EDITPHENOMENON_H
#define EDITPHENOMENON_H

#include <QDialog>

namespace Ui {
class EditPhenomenon;
}

class EditPhenomenon : public QDialog
{
    Q_OBJECT

public:
    explicit EditPhenomenon(QWidget *parent = 0);
    ~EditPhenomenon();

private:
    Ui::EditPhenomenon *ui;
};

#endif // EDITPHENOMENON_H
