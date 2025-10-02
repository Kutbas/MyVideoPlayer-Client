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

    // 用户点击修改密码，弹出修改密码对话框，输入密码后点击提交，此时拿到的密码肯定不为空
    // 用户再次点击修改密码，弹出修改密码对话框，输入密码后点击取消，此时拿的密码为空
    // 如果直接将从修改密码对话框获取到的密码设置到新密码中，那么随着第二次的取消动作，将使得第一次修改的值也被取消
    const QString &password = dlg->getPassword();
    if (password.isEmpty())
    {
        LOG() << "取消密码设置";
        return;
    }

    LOG() << "新密码已设置：" << password;

    // 隐藏修改密码的按钮，显示已经修改
    ui->passwordBtn->hide();
    ui->passwordWidget->show();

    delete dlg;
}