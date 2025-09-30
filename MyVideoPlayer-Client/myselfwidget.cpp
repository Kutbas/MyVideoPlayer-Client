#include "myselfwidget.h"
#include "ui_myselfwidget.h"
#include "videobox.h"
#include "util.h"
#include <QFileDialog>

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

    connect(ui->avatarBtn, &QPushButton::clicked, this, &MyselfWidget::onAvatarBtnClicked);
}

void MyselfWidget::onAvatarBtnClicked()
{
    // 弹出对话框，从本地磁盘选择图片
    QString fileName = QFileDialog::getOpenFileName(nullptr, "修改图像", "", tr("Images (*.png *.jpg)"));
    if (fileName.isEmpty())
    {
        LOG() << "选择头像取消";
        return;
    }

    LOG() << fileName;

    // 获取图片数据
    QByteArray fileData = loadFileToByteArray(fileName);
    if (fileData.isEmpty())
    {
        LOG() << "读取文件失败！";
        return;
    }

    // 将图片数据设置成按钮图标
    ui->avatarBtn->setIcon(makeCircleIcon(fileData, ui->avatarBtn->width() / 2));

    // 将图片数据上传到服务器
}