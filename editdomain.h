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
    void setDomainName(QString name);
    void setDomainDescription(QString desc);
    void setDomainType(QString type);
    ~EditDomain();

signals:
    void updateName(QString);
    void updateDescription(QString);
    void updateType(QString);

private slots:
    void on_okButton_clicked();


private:
    Ui::EditDomain *ui;
};

#endif // EDITDOMAIN_H
