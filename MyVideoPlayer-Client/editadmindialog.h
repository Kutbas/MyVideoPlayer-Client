#ifndef EDITADMINDIALOG_H
#define EDITADMINDIALOG_H

#include <QWidget>

namespace Ui {
class EditAdminDialog;
}

class EditAdminDialog : public QWidget
{
    Q_OBJECT

public:
    explicit EditAdminDialog(QWidget *parent = nullptr);
    ~EditAdminDialog();

private:
    Ui::EditAdminDialog *ui;
};

#endif // EDITADMINDIALOG_H
