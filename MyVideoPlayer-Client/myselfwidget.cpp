#include "myselfwidget.h"
#include "ui_myselfwidget.h"
#include "videobox.h"
#include "util.h"

MyselfWidget::MyselfWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MyselfWidget)
{
    ui->setupUi(this);
    initUI();
}

MyselfWidget::~MyselfWidget()
{
    delete ui;
}

void MyselfWidget::initUI()
{
    ui->attentionBtn->hide();

    #ifdef TEST_UI
    // 向视频显示区域添加VideoBox，测试代码
    for (int i = 0; i < 16; i++)
    {
        VideoBox *videoBox = new VideoBox();
        ui->layout->addWidget(videoBox, i / 4, i % 4);
    }
    #endif
}
