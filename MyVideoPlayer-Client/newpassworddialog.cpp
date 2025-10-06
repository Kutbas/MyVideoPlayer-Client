#include "newpassworddialog.h"
#include "ui_newpassworddialog.h"
#include "util.h"

NewPasswordDialog::NewPasswordDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::NewPasswordDialog)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);

    connect(ui->submitBtn, &QPushButton::clicked, this, &NewPasswordDialog::onSubmitBtnClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::close);

    connect(ui->passwordEdit1, &QLineEdit::editingFinished, this, &NewPasswordDialog::onEdittingFinished);
    connect(ui->passwordEdit2, &QLineEdit::editingFinished, this, &NewPasswordDialog::onEdittingFinished);
}

NewPasswordDialog::~NewPasswordDialog()
{
    delete ui;
}

void NewPasswordDialog::onEdittingFinished()
{
    checkPasswordEdit();
}

bool NewPasswordDialog::checkPasswordEdit()
{
    // 检测密码是否为空
    if (ui->passwordEdit1->text().isEmpty() || ui->passwordEdit2->text().isEmpty())
    {
        ui->messageLabel->setText("密码不能为空！");
        return false;
    }

    // 检测密码是否符合条件
    QString message = passwordValid(ui->passwordEdit1->text());

    if (!message.isEmpty())
    {
        ui->messageLabel->setText(message);
        return false;
    }

    message = passwordValid(ui->passwordEdit2->text());
    if (!message.isEmpty())
    {
        ui->messageLabel->setText(message);
        return false;
    }

    // 检测两次输入的密码是否一致
    if (ui->passwordEdit1->text() != ui->passwordEdit2->text())
    {
        ui->messageLabel->setText("两次输入的密码不一致！");
        return false;
    }

    ui->messageLabel->setText("");
    return true;
}

// 检测失败时，返回失败的原因
QString NewPasswordDialog::passwordValid(const QString &password)
{
    // 密码条件：包含大小写字母，数字以及标点符号，至少包含两种类型的字符，长度必须在8~16位之间
    if (password.length() < 8)
        return QString("密码长度不能小于8位！");

    if (password.length() > 16)
        return QString("密码长度不能大于16位！");

    // 检测密码中的字母是否满足：大小写字母、数字及标点符号
    // 同时统计字符种类的信息
    enum CharType
    {
        Upper,
        Lower,
        Digit,
        Punct
    };

    // 用来记录某种字符是否出现过
    QMap<CharType, int> charTypeMap;

    for (int i = 0; i < password.length(); i++)
    {
        QChar ch = password[i];
        if (ch.isUpper())
        {
            charTypeMap[Upper] = 1;
        }
        else if (ch.isLower())
        {
            charTypeMap[Lower] = 1;
        }
        else if (ch.isDigit())
        {
            charTypeMap[Digit] = 1;
        }
        else if (ch.isPunct())
        {
            charTypeMap[Punct] = 1;
        }
        else
            return QString("密码中只能包含数字、字符及标点符号！");
    }

    // 检测密码是否至少包含两种不同的字符
    int totalCount = 0;
    for (auto &e : charTypeMap)
        totalCount += e;

    if (totalCount < 2)
        return QString("密码中必须包含至少两类字符！");

    return QString("");
}

void NewPasswordDialog::onSubmitBtnClicked()
{
    if (!checkPasswordEdit())
        return;

    // 保存密码
    password = ui->passwordEdit1->text();

    close();
}

const QString &NewPasswordDialog::getPassword() const
{
    return password;
}