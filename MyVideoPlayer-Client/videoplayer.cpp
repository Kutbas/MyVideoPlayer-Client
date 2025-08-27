#include "videoplayer.h"
#include "ui_videoplayer.h"
#include "util.h"
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    initUI();

    connectSignalAndSlot();
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

// 初始化界面UI
void VideoPlayer::initUI()
{
    setWindowFlag(Qt::FramelessWindowHint);             // 去除窗口的边框
    setAttribute(Qt::WA_TranslucentBackground);         // 将窗口设置为透明
    setWindowIcon(QIcon(":/images/homePage/logo.png")); // 设置窗口的图标

    // 给窗口添加阴影效果
    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect(this);
    dropShadow->setColor(Qt::black);           // 设置阴影颜色
    dropShadow->setBlurRadius(5);              // 设置圆角半径
    dropShadow->setOffset(0, 0);               // 设置阴影偏移量
    ui->MainBg->setGraphicsEffect(dropShadow); // 将阴影效果添加到主界面背景上
    // 设置页面切换按钮的文本和图片和颜色，同时建立按钮和页面的关系
    ui->homePageBtn->setTextColor("#000000");
    ui->homePageBtn->setImageAndText(":/images/homePage/shouyexuan.png", "首页", HomePage);
    ui->myPageBtn->setImageAndText(":/images/homePage/wode.png", "我的", MyPage);
    ui->myPageBtn->setTextColor("#999999");
    ui->sysPageBtn->setImageAndText(":/images/homePage/admin.png", "系统", AdminPage);
    ui->sysPageBtn->setTextColor("#999999");
}

// 绑定信号槽
void VideoPlayer::connectSignalAndSlot()
{
    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);                 // 最小化按钮
    connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);                        // 关闭按钮
    connect(ui->homePageBtn, &PageSwitchButton::switchPage, this, &VideoPlayer::onSwitchPage); // 切换至首页
    connect(ui->myPageBtn, &PageSwitchButton::switchPage, this, &VideoPlayer::onSwitchPage);   // 切换至我的
    connect(ui->sysPageBtn, &PageSwitchButton::switchPage, this, &VideoPlayer::onSwitchPage);  // 切换至系统
}

// 鼠标单击
void VideoPlayer::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->position().toPoint(); // 获取鼠标点击的位置

    // 检测鼠标左键单击时该位置是否在 head 中
    if (ui->head->geometry().contains(point))
    {
        if (event->button() == Qt::LeftButton)
        {
            dragPos = event->globalPosition().toPoint() - geometry().topLeft(); // 保存相对位置
            return;
        }
    }

    QWidget::mousePressEvent(event);
}

// 鼠标移动
void VideoPlayer::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->position().toPoint(); // 获取鼠标点击的位置

    // 检测鼠标左键移动时该位置是否在 head 中
    if (ui->head->geometry().contains(point))
    {
        if (event->buttons() == Qt::LeftButton)
        {
            move(event->globalPosition().toPoint() - dragPos); // 把窗口移动到新的位置
            return;
        }
    }
}

// 为 UI 界面中的层叠窗口设置当前索引
void VideoPlayer::onSwitchPage(int pageId)
{
    ui->stackedWidget->setCurrentIndex(pageId);
    resetSwitchBtnInfo(pageId);
}

// 重置页面按钮信息
void VideoPlayer::resetSwitchBtnInfo(int pageId)
{
    QList<PageSwitchButton *> switchBtns = findChildren<PageSwitchButton *>();
    for (auto switchBtn : switchBtns)
    {
        // 没被点击的按钮才重置信息
        if (switchBtn->getPageId() != pageId)
        {
            switchBtn->setTextColor("#999999");
        }
    }

    // 重置按钮图片的颜色
    if (pageId == HomePage)
    {
        ui->homePageBtn->setImage(":/images/homePage/shouyexuan.png");
        ui->myPageBtn->setImage(":/images/homePage/wode.png");
        ui->sysPageBtn->setImage(":/images/homePage/admin.png");
    }
    else if (pageId == MyPage)
    {
        ui->homePageBtn->setImage(":/images/homePage/shouye.png");
        ui->myPageBtn->setImage(":/images/homePage/wodexuan.png");
        ui->sysPageBtn->setImage(":/images/homePage/admin.png");
    }
    else if (pageId == AdminPage)
    {
        ui->homePageBtn->setImage(":/images/homePage/shouye.png");
        ui->myPageBtn->setImage(":/images/homePage/wode.png");
        ui->sysPageBtn->setImage(":/images/homePage/adminxuan.png");
    }
    else
        LOG() << "暂不支持的按钮";
}
