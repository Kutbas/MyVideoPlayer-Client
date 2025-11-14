#include "login.h"
#include "ui_login.h"
#include <QRegularExpressionValidator>
#include <QGraphicsDropShadowEffect>

Login::Login(QWidget *parent)
    : QWidget(parent), ui(new Ui::Login)
{
    ui->setupUi(this);

    // 去除窗口边框，并设置窗口为模态对话框
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_ShowModal, true);

    // 给窗口添加阴影效果
    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect(this);
    dropShadow->setColor(Qt::black);            // 设置阴影颜色
    dropShadow->setBlurRadius(3);               // 设置圆角半径
    dropShadow->setOffset(0, 0);                // 设置阴影偏移量
    ui->loginBg->setGraphicsEffect(dropShadow); // 将阴影效果添加到主界面背景上

    ui->passwordNum->setEchoMode(QLineEdit::Password);

    // 手机号编辑框限制
    QRegularExpression regExp("^1\\d{10}$");
    QValidator *validator = new QRegularExpressionValidator(regExp, this);
    // ui->accountNum->setValidator(validator);
    ui->phoneNum->setValidator(validator);

    // 验证码限制
    QIntValidator *intValid = new QIntValidator(0, 999999, ui->authcode);
    ui->authcode->setValidator(intValid);
    ui->authcode->setMaxLength(6);

    // 默认显示短信登录
    ui->messageWidget->show();
    ui->passwordWidget->hide();

    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);

    // 切换账号密码登录
    connect(ui->passwordBtn, &QPushButton::clicked, this, &Login::onPasswordBtnClicked);
    // 切换短信登录
    connect(ui->messageBtn, &QPushButton::clicked, this, &Login::onMessageBtnClicked);
}

Login::~Login()
{
    delete ui;
}

void Login::onPasswordBtnClicked()
{
    ui->messageWidget->hide();
    ui->passwordWidget->show();

    ui->passwordBtn->setStyleSheet("QPushButton{"
                                   "color : #3ECEFE;"
                                   "font-weight:bold;"
                                   "border : none;"
                                   "border-bottom : 6px solid #3ECEFE;}");

    ui->messageBtn->setStyleSheet("QPushButton{"
                                  "color : #222222;"
                                  "border : none;"
                                  "border-bottom: 2px solid #B5ECFF;}");
}

void Login::onMessageBtnClicked()
{
    ui->messageWidget->show();
    ui->passwordWidget->hide();

    ui->messageBtn->setStyleSheet("QPushButton{"
                                  "color : #3ECEFE;"
                                  "font-weight:bold;"
                                  "border : none;"
                                  "border-bottom : 6px solid #3ECEFE;}");

    ui->passwordBtn->setStyleSheet("QPushButton{"
                                   "color : #222222;"
                                   "border : none;"
                                   "border-bottom: 2px solid #B5ECFF;}");
}
