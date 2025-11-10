#include "roletable.h"
#include "ui_roletable.h"
#include "util.h"
#include "roletableitem.h"
#include "editadmindialog.h"

RoleTable::RoleTable(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoleTable)
{
    ui->setupUi(this);

    ui->userStatus->addItem("全部分类");
    ui->userStatus->addItem("启用");
    ui->userStatus->addItem("停用");
    ui->userStatus->setCurrentIndex(0);

    // 限制编辑框只能输入手机号
    QRegularExpression regExp("^1\\d{10}$");
    QValidator *validator = new QRegularExpressionValidator(regExp, this);
    // 将正则表达式校验器设置到编辑框中
    ui->phone->setValidator(validator);

    initStyle();
    updateRoleTable();

    connect(ui->resetBtn, &QPushButton::clicked, this, &RoleTable::onResetBtnClicked);
    connect(ui->queryBtn, &QPushButton::clicked, this, &RoleTable::onQueryBtnClicked);
    connect(ui->insertBtn, &QPushButton::clicked, this, &RoleTable::onInsertBtnClicked);
}

RoleTable::~RoleTable()
{
    delete ui;
}

void RoleTable::onResetBtnClicked()
{
    // 设置重置按钮高亮
    ui->resetBtn->setStyleSheet(styleSheet["选中"]);
    ui->queryBtn->setStyleSheet(styleSheet["未选中"]);

    ui->phone->setText("");
    ui->userStatus->setCurrentIndex(0);
    LOG() << "点击重置按钮";
}

void RoleTable::onQueryBtnClicked()
{
    // 设置查询按钮高亮
    ui->queryBtn->setStyleSheet(styleSheet["选中"]);
    ui->resetBtn->setStyleSheet(styleSheet["未选中"]);

    LOG() << "点击查询按钮";
}

void RoleTable::initStyle()
{
    styleSheet.insert("选中", "background-color:#3ECEFF;"
                              "border-radius:4px;"
                              "font-family:微软雅黑;"
                              "font-size:14px;"
                              "color:white;");

    styleSheet.insert("未选中", "background-color:white;"
                                "border-radius:4px;"
                                "border:1px solid #DCDEE0;"
                                "font-family:微软雅黑;"
                                "font-size:14px;"
                                "color:#222222;");
}

void RoleTable::updateRoleTable()
{
    for (int i = 0; i < 20; i++)
    {
        RoleTableItem *roleItem = new RoleTableItem(this, i + 1);
        ui->layout->addWidget(roleItem);
    }
}

void RoleTable::onInsertBtnClicked()
{
    EditAdminDialog *editAdminDlg = new EditAdminDialog(nullptr, "新增后台用户");
    editAdminDlg->exec();
    delete editAdminDlg;
}