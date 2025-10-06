#include "videobox.h"
#include "ui_videobox.h"
#include "util.h"

VideoBox::VideoBox(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoBox)
{
    ui->setupUi(this);
    ui->delVideoBtn->hide();

    playPage = new PlayPage();

    // 给视频封面、视频标题控件安装拦截器
    ui->imageBox->installEventFilter(this);
    ui->videoTittle->installEventFilter(this);
}

VideoBox::~VideoBox()
{
    delete ui;
}

bool VideoBox::eventFilter(QObject *watched, QEvent *event)
{
    if (ui->imageBox == watched || ui->videoTittle == watched)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            // 显示播放窗口
            onPlayClicked();
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

void VideoBox::onPlayClicked()
{
    playPage->show();
}
