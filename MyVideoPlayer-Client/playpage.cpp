#include "playpage.h"
#include "ui_playpage.h"
#include <QMouseEvent>
#include "login.h"
#include "toast.h"
#include "util.h"

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal);

    volume = new Volume(this);
    playSpeed = new PlaySpeed(this);

    mpvPlayer = new MpvPlayer(ui->screen);

    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->volumeBtn, &QPushButton::clicked, this, &PlayPage::onVolumeBtnClicked);
    connect(ui->speedBtn, &QPushButton::clicked, this, &PlayPage::onSpeedBtnClicked);
    connect(ui->likeImageBtn, &QPushButton::clicked, this, &PlayPage::onLikeImageBtnClicked);
    connect(ui->playBtn, &QPushButton::clicked, this, &PlayPage::onPlayBtnClicked);
    connect(playSpeed, &PlaySpeed::setPlaySpeed, this, &PlayPage::onPlaySpeedChanged);
    connect(volume, &Volume::setVolume, this, &PlayPage::setVolume);                             // 设置音量
    connect(mpvPlayer, &MpvPlayer::playPositionChanged, this, &PlayPage::onPlayPositionChanged); // 播放进度调整
}

PlayPage::~PlayPage()
{
    delete ui;
    delete mpvPlayer;
}

void PlayPage::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->position().toPoint(); // 获取鼠标点击的位置

    // 检测鼠标左键单击时该位置是否在 head 中
    if (ui->playHead->geometry().contains(point))
    {
        if (event->button() == Qt::LeftButton)
        {
            dragPos = event->globalPosition().toPoint() - geometry().topLeft(); // 保存相对位置
            return;
        }
    }

    QWidget::mousePressEvent(event);
}

void PlayPage::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->position().toPoint(); // 获取鼠标点击的位置

    // 检测鼠标左键移动时该位置是否在 head 中
    if (ui->playHead->geometry().contains(point))
    {
        if (event->buttons() == Qt::LeftButton)
        {
            move(event->globalPosition().toPoint() - dragPos); // 把窗口移动到新的位置
            return;
        }
    }
}

void PlayPage::onVolumeBtnClicked()
{
    // 获取播放窗口的左上角坐标，并将其转换为基于桌面的坐标
    moveWindows(mapToGlobal(QPoint(0, 0)));
    volume->show();
}

void PlayPage::moveWindows(const QPoint &point)
{
    // point 已经是基于屏幕的全局坐标
    QPoint newPoint = point + QPoint(this->width() - volume->width() - 13, 533);
    volume->move(newPoint);

    newPoint = point + QPoint(this->width() - playSpeed->width() - 80, 536);
    playSpeed->move(newPoint);
}

void PlayPage::onSpeedBtnClicked()
{
    moveWindows(mapToGlobal(QPoint(0, 0)));
    playSpeed->show();
}

void PlayPage::onLikeImageBtnClicked()
{
    Login *login = new Login();
    Toast::showMessage("先登录，再点赞！", login);
}

void PlayPage::startPlaying(const QString &videoPath)
{
    // 保存当前播放视频路径，播放结束时点击再次播放时需要用到
    this->videoPath = videoPath;

    mpvPlayer->startPlay(videoPath);

    mpvPlayer->pause();
}

void PlayPage::onPlayBtnClicked()
{
    isPlay = !isPlay;
    if (isPlay)
    {
        ui->playBtn->setStyleSheet("border-image:url(:/images/PlayPage/bofang.png)");
        mpvPlayer->play();
    }
    else
    {
        ui->playBtn->setStyleSheet("border-image:url(:/images/PlayPage/zanting.png)");
        mpvPlayer->pause();
    }

    if (playTime == 10 && isPlay)
    {
        // 播放位置修改到起始为⽌，⽤⼾点击播放按钮可以重新播放
        this->playTime = 0;
        startPlaying(videoPath);
        mpvPlayer->play();
    }
}

void PlayPage::onPlaySpeedChanged(double speed)
{
    mpvPlayer->setPlaySpeed(speed);
}

void PlayPage::setVolume(int volume)
{
    mpvPlayer->setVolume(volume);
}

void PlayPage::onPlayPositionChanged(int64_t playTime)
{
    this->playTime = playTime;

    QString curPlayTime = secondToTime(playTime);
    QString totalTime = secondToTime(10); //  // 此处10是测试视频时长，视频时长将来是从视频文件中获取
    ui->videoDuration->setText(curPlayTime + "/" + totalTime);

    // 修改进度条
    ui->videoSlider->setPlayStep((double)playTime / 10);

    // 当播放结束时，设置播放按钮为暂停状态

    if (playTime == 10)
    {
        // 视频播放完毕，更新播放按钮图标
        // 此时播放按钮应该变为暂停

        isPlay = false;
        ui->playBtn->setStyleSheet("border-image : url(:/images/PlayPage/zanting.png)");
    }
}

QString PlayPage::secondToTime(int64_t seconds)
{
    QString time;

    // ⼩时存在时才显⽰
    if (seconds / 60 / 60)
        time += QString::asprintf("%02lld:", seconds / 60 / 60);

    // 拼接上分和秒
    time += QString::asprintf("%02lld:%02lld", seconds / 60, seconds % 60);

    return time;
}