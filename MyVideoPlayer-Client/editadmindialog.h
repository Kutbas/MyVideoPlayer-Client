#ifndef EDITADMINDIALOG_H
#define EDITADMINDIALOG_H

#include <QDialog>

namespace Ui
{
    class EditAdminDialog;
}

class EditAdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAdminDialog(QWidget *parent = nullptr, const QString &text = "新增后台用户");
    ~EditAdminDialog();

private slots:
    void onSubmitBtnClicked();
    void onCancelBtnClicked();

private:
    Ui::EditAdminDialog *ui;
};

#endif // EDITADMINDIALOG_H
