#include "roletable.h"
#include "ui_roletable.h"

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
}

RoleTable::~RoleTable()
{
    delete ui;
}
