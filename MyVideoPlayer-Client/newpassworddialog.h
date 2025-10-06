#ifndef NEWPASSWORDDIALOG_H
#define NEWPASSWORDDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui
{
    class NewPasswordDialog;
}

class NewPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPasswordDialog(QWidget *parent = nullptr);
    ~NewPasswordDialog();
    const QString &getPassword() const;

private slots:
    void onEdittingFinished();
    void onSubmitBtnClicked();

private:
    bool checkPasswordEdit();
    QString passwordValid(const QString &password);

private:
    Ui::NewPasswordDialog *ui;
    QString password;
};

#endif // NEWPASSWORDDIALOG_H
