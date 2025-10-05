#include "myselfwidget.h"
#include "ui_myselfwidget.h"
#include "videobox.h"
#include "util.h"
#include <QFileDialog>
#include <QFileInfo>
#include "modifymyselfdialog.h"
#include "videoplayer.h"

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
    connect(ui->settingBtn, &QPushButton::clicked, this, &MyselfWidget::onSettingBtnClicked);
    connect(ui->uploadVideoBtn, &QPushButton::clicked, this, &MyselfWidget::onUploadVideoBtnClicked);
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

void MyselfWidget::onSettingBtnClicked()
{
    ModifyMyselfDialog *dlg = new ModifyMyselfDialog();
    dlg->exec();
    delete dlg;
}

void MyselfWidget::onUploadVideoBtnClicked()
{
    // 弹出打开文件对话框，让用户选择要上传的视频文件
    QString fileName = QFileDialog::getOpenFileName(nullptr, "上传视频", "", tr("Videos (*.mp4 *.rmvb *.avi *.mov)"));
    if (fileName.isEmpty())
    {
        LOG() << "上传视频取消";
        return;
    }
    LOG() << fileName;

    // 检测视频大小，不能超过4G
    QFileInfo fileInfo(fileName);
    int64_t fileSize = fileInfo.size();
    if (fileSize > (int64_t)1024 * 1024 * 1024 * 4)
    {
        LOG() << "视频大小不能超过4G！";
        return;
    }

    // 上传视频

    // 切换到上传视频页面
    emit switchUploadVideoPage(UploadPage);
}