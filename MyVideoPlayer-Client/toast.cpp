#include "toast.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QApplication>
#include <QScreen>

Toast::Toast(const QString &text)
{
    initUI(text);

    // 定义定时器
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]()
            {
        timer->stop();
        this->close();
        this->deleteLater(); });
    timer->start(2000);
}

Toast::Toast(const QString &text, QWidget *widget)
{
    initUI(text);

    // 定义定时器
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]()
            {
        timer->stop();
        this->close();
        this->deleteLater();
        if(widget){
        widget->show();
     } });
    timer->start(2000);
}

void Toast::initUI(const QString &text)
{
    // 去掉窗口的标题栏
    // Tool:让窗口浮动在主窗口上，窗口的图标也不会在任务栏上显示
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(800, 60);

    // 给窗口添加背景
    QWidget *toastBg = new QWidget(this);
    toastBg->setFixedSize(800, 60);
    toastBg->setStyleSheet("background-color : rgba(102,102,102,0.5);"
                           "border-radius : 4px;");

    // 界面设置
    QVBoxLayout *layout = new QVBoxLayout(toastBg);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    toastBg->setLayout(layout);

    // 创建显显示文本的Label
    QLabel *label = new QLabel(toastBg);
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);
    // Expanding:控件的大小会随着父窗口的变化而扩展
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setStyleSheet("font-family: 微软雅黑;"
                         "font-size: 14px;"
                         "color : #FFFFFF;");
    layout->addWidget(label);

    // 设置窗口的位置：尽量在主屏幕的中间偏下
    QScreen *screen = QApplication::primaryScreen();
    int width = screen->size().width();
    int height = screen->size().height();
    int x = (width - this->width()) / 2;
    int y = height - this->height() - 100;

    this->move(x, y);
}

void Toast::showMessage(const QString &text)
{
    Toast *toast = new Toast(text);
    toast->show();
}

void Toast::showMessage(const QString &text, QWidget *widget)
{
    Toast *toast = new Toast(text, widget);
    toast->show();
}