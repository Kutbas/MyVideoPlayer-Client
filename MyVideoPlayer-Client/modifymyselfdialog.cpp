#include "modifymyselfdialog.h"
#include "ui_modifymyselfdialog.h"
#include "util.h"
#include "newpassworddialog.h"

ModifyMyselfDialog::ModifyMyselfDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ModifyMyselfDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    ui->passwordWidget->hide();

    connect(ui->submitBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::onSubmitBtnClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::onCancelBtnClicked);
    connect(ui->passwordBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::showPasswordDlg);
    connect(ui->changePasswordBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::showPasswordDlg);
}

ModifyMyselfDialog::~ModifyMyselfDialog()
{
    delete ui;
}

void ModifyMyselfDialog::onSubmitBtnClicked()
{
    LOG() << "提交";
}

void ModifyMyselfDialog::onCancelBtnClicked()
{
    close();
}

void ModifyMyselfDialog::showPasswordDlg()
{
    NewPasswordDialog *dlg = new NewPasswordDialog();
    dlg->exec();
    delete dlg;
}