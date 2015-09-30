#ifndef EDITDOMAIN_H
#define EDITDOMAIN_H

#include <QDialog>

namespace Ui {
class EditDomain;
}

class EditDomain : public QDialog
{
    Q_OBJECT

public:
    explicit EditDomain(QWidget *parent = 0);
    ~EditDomain();

private:
    Ui::EditDomain *ui;
};

#endif // EDITDOMAIN_H
