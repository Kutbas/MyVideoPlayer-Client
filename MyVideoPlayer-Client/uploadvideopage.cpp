#include "uploadvideopage.h"
#include "ui_uploadvideopage.h"
#include "videoplayer.h"

UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::UploadVideoPage)
{
    ui->setupUi(this);

    connect(ui->commitBtn, &QPushButton::clicked, this, &UploadVideoPage::onCommitBtnClicked);
}

UploadVideoPage::~UploadVideoPage()
{
    delete ui;
}

void UploadVideoPage::onCommitBtnClicked()
{
    // 将页面中的视频信息上传到服务器

    // 切换回我的页面
    emit switchMyselfPage(MyPage);
}
