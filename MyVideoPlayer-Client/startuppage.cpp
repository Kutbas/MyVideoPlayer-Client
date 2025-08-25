#include "startuppage.h"
#include <QLabel>
#include <QTimer>

StartupPage::StartupPage(QDialog *parent)
    : QDialog{parent}
{

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); // 无边框设置+任务栏不显示图标

    setFixedSize(1450,860);
    setStyleSheet("background-color : #FFFFFF");

    // 在窗口中显示图片
    QPixmap pix(":/images/startupPage/biteshipin.png");
    if (pix.isNull()) {
        qDebug() << "图片加载失败!";
    }

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(pix);
    imageLabel->move(524,374);
}

void StartupPage::startTimer()
{
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [=]{
        timer->stop();
        delete timer;
        close();
    });

    timer->start(2000); // 2000ms
}
