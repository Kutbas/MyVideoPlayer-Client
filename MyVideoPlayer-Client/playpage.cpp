#include "playpage.h"
#include "ui_playpage.h"
#include <QMouseEvent>

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal);

    volume = new Volume(this);
    playSpeed = new PlaySpeed(this);

    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->volumeBtn, &QPushButton::clicked, this, &PlayPage::onVolumeBtnClicked);
    connect(ui->speedBtn, &QPushButton::clicked, this, &PlayPage::onSpeedBtnClicked);
}

PlayPage::~PlayPage()
{
    delete ui;
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