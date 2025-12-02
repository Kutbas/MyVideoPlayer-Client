#include "playpage.h"
#include "ui_playpage.h"
#include <QMouseEvent>
#include "login.h"
#include "toast.h"
#include "util.h"
#include <QShortcut>

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal);

    volume = new Volume(this);
    playSpeed = new PlaySpeed(this);

    mpvPlayer = new MpvPlayer(ui->screen);

    initBarrageArea();

    // 播放按钮绑定空格快捷键
    QShortcut *shortCut = new QShortcut(ui->playBtn);
    QKeySequence keySequence(" ");
    shortCut->setKey(keySequence);
    connect(shortCut, &QShortcut::activated, this, [&]()
            { ui->playBtn->animateClick(); });

    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->volumeBtn, &QPushButton::clicked, this, &PlayPage::onVolumeBtnClicked);
    connect(ui->speedBtn, &QPushButton::clicked, this, &PlayPage::onSpeedBtnClicked);
    connect(ui->likeImageBtn, &QPushButton::clicked, this, &PlayPage::onLikeImageBtnClicked);
    connect(ui->playBtn, &QPushButton::clicked, this, &PlayPage::onPlayBtnClicked);
    connect(playSpeed, &PlaySpeed::setPlaySpeed, this, &PlayPage::onPlaySpeedChanged);
    connect(volume, &Volume::setVolume, this, &PlayPage::setVolume);                             // 设置音量
    connect(mpvPlayer, &MpvPlayer::playPositionChanged, this, &PlayPage::onPlayPositionChanged); // 播放进度调整
    connect(ui->videoSlider, &PlaySlider::setPlayProgress, this, &PlayPage::setPlayProgress);    // 播放进度调整
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

void PlayPage::setPlayProgress(double playRatio)
{
    // 根据进度条的比例计算当前的播放时间
    playTime = playRatio * 10;

    mpvPlayer->setCurrentPlayPosition(playTime);
}

void PlayPage::initBarrageArea()
{
    // 创建弹幕的显示区域对话框，该对话框无边框，背景透明
    barrageArea = new QDialog(this);
    barrageArea->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    barrageArea->setAttribute(Qt::WA_TranslucentBackground);
    barrageArea->setMinimumSize(this->width(), 38 * 3);

    // 创建垂直布局器，添加到对话框中
    QVBoxLayout *layout = new QVBoxLayout(barrageArea);
    barrageArea->setLayout(layout);

    // 在弹幕区域添加用来显示三行弹幕的控件
    top = new QFrame(this);
    top->setFixedSize(this->width(), 38);
    // top->setStyleSheet("background-color:red;");

    middle = new QFrame(this);
    middle->setFixedSize(this->width(), 38);
    // middle->setStyleSheet("background-color:green;");

    bottom = new QFrame(this);
    bottom->setFixedSize(this->width(), 38);
    // bottom->setStyleSheet("background-color:blue;");

    layout->addWidget(top);
    layout->addWidget(middle);
    layout->addWidget(bottom);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 移动弹幕窗口到播放窗口的 head 底下
    QPoint point = mapToGlobal(QPoint(0, 0));
    point.setY(point.y() + ui->playHead->height());
    barrageArea->move(point);
    barrageArea->show();
}