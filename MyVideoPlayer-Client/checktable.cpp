#include "checktable.h"
#include "ui_checktable.h"
#include "util.h"

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

    connect(ui->resetBtn, &QPushButton::clicked, this, &CheckTable::onResetBtnClicked);
    connect(ui->queryBtn, &QPushButton::clicked, this, &CheckTable::onQueryBtnClicked);
}

CheckTable::~CheckTable()
{
    delete ui;
}

void CheckTable::onResetBtnClicked()
{
    // 设置重置按钮高亮
    ui->resetBtn->setStyleSheet("background-color:#3ECEFF;"
                                "border-radius:4px;"
                                "font-family:微软雅黑;"
                                "font-size:14px;"
                                "color:white;");

    ui->queryBtn->setStyleSheet("background-color:white;"
                                "border-radius:4px;"
                                "border:1px solid #DCDEE0;"
                                "font-family:微软雅黑;"
                                "font-size:14px;"
                                "color:#222222;");

    ui->userIdEdit->setText("");
    ui->videoStatus->setCurrentIndex(0);
    LOG() << "点击重置按钮";
}

void CheckTable::onQueryBtnClicked()
{
    // 设置查询按钮高亮
    ui->queryBtn->setStyleSheet("background-color:#3ECEFF;"
                                "border-radius:4px;"
                                "font-family:微软雅黑;"
                                "font-size:14px;"
                                "color:white;");

    ui->resetBtn->setStyleSheet("background-color:white;"
                                "border-radius:4px;"
                                "border:1px solid #DCDEE0;"
                                "font-family:微软雅黑;"
                                "font-size:14px;"
                                "color:#222222;");

    LOG() << "查询重置按钮";
}
