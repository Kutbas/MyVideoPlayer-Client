#include "checktable.h"
#include "ui_checktable.h"

CheckTable::CheckTable(QWidget *parent)
    : QWidget(parent), ui(new Ui::CheckTable)
{
    ui->setupUi(this);
    ui->videoStatus->addItem("全部分类");
    ui->videoStatus->addItem("待审核");
    ui->videoStatus->addItem("审核通过");
    ui->videoStatus->addItem("审核驳回");
    ui->videoStatus->addItem("已下架");
    ui->videoStatus->addItem("转码中");



    // 给视频用户编辑框添加限制
    QRegularExpression regExp("^[0-9a-f]{4}-[0-9a-f]{8}-[0-9a-f]{4}$");
    QValidator *validator = new QRegularExpressionValidator(regExp, this);

    // 将正则表达式校验器设置到编辑框中
    ui->userIdEdit->setValidator(validator);
}

CheckTable::~CheckTable()
{
    delete ui;
}
