#ifndef EDITINTERFACE_H
#define EDITINTERFACE_H

/*******************************************************************************
/*! \class editinterface.h
 *
 *  A dialog that appears when editing interface properties
*******************************************************************************/
#include <QDialog>

namespace Ui {
class EditInterface;
}

class EditInterface : public QDialog
{
    Q_OBJECT

public:
    explicit EditInterface(QWidget *parent = 0);
    void setInterfaceDescription(QString desc);
    void setInterfaceName(QString name);
    ~EditInterface();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();

signals:
    void updateDescription(QString);
    void updateName(QString);

private:
    Ui::EditInterface *ui;
};

#endif // EDITINTERFACE_H
