#include "playslider.h"
#include "ui_playslider.h"
#include <QMouseEvent>
#include "util.h"

PlaySlider::PlaySlider(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlaySlider)
{
    ui->setupUi(this);
    playProgress = 0;
}

PlaySlider::~PlaySlider()
{
    delete ui;
}

// 鼠标点击
void PlaySlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        playProgress = event->pos().x(); // 鼠标左键按下时，需要记录当前鼠标的 x 轴位置
        moveSlider();
        return;
    }

    QWidget::mousePressEvent(event);
}

// 鼠标释放
void PlaySlider::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        playProgress = event->pos().x(); // 鼠标左键按下时，需要记录当前鼠标的 x 轴位置
        moveSlider();
        return;
    }

    QWidget::mouseReleaseEvent(event);
}

// 鼠标移动
void PlaySlider::mouseMoveEvent(QMouseEvent *event)
{
    // 检测鼠标的位置是否在进度条的窗口中
    if (!this->geometry().contains(event->pos()))
    {
        LOG() << event->pos();
        return;
    }

    if (event->buttons() == Qt::LeftButton)
    {
        playProgress = event->pos().x();

        if (playProgress < 0)
            playProgress = 0;

        int maxWidth = this->width();
        if (playProgress > maxWidth)
            playProgress = maxWidth;

        moveSlider();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void PlaySlider::moveSlider()
{
    // 更改 outLine 到 playProgress 的宽度
    ui->outLine->setGeometry(ui->outLine->x(), ui->outLine->y(), playProgress, ui->outLine->height());
}