#include "uploadvideopage.h"
#include "ui_uploadvideopage.h"

UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UploadVideoPage)
{
    ui->setupUi(this);
}

UploadVideoPage::~UploadVideoPage()
{
    delete ui;
}
