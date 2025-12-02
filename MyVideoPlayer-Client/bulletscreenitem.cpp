#include "bulletscreenitem.h"
#include <QHBoxLayout>

BulletScreenItem::BulletScreenItem(QWidget *parent)
    : QFrame{parent}
{
    setFixedHeight(38);

    // 弹幕文本和用户头像在水平布局器中
    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);

    // 用户头像
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(30, 30);
    imageLabel->setScaledContents(true);
    imageLabel->hide(); // 默认情况下不展示头像

    // 弹幕文本
    textLabel = new QLabel(this);
    textLabel->setStyleSheet("font-family : 微软雅黑;"
                             "font-size : 18px;"
                             "color : #FFFFFF;"
                             "border : none;");
    textLabel->adjustSize();

    // 将元素添加到水平布局器中
    layout->addWidget(imageLabel);
    layout->addWidget(textLabel);
    layout->setContentsMargins(10, 4, 19, 4);
    layout->setSpacing(0);
}

void BulletScreenItem::setBulletScreenText(const QString &text)
{
    textLabel->setText(text);
    textLabel->adjustSize();
}

void BulletScreenItem::setBulletScreenIcon(QPixmap &pixmap)
{
    imageLabel->setPixmap(pixmap);
    imageLabel->show();
    this->setStyleSheet("#QFrame{"
                        "border : 1px solid #3ECEFE;"
                        "border-radius : 19px;}");
}

void BulletScreenItem::setBulletScreenAnimal(int x, int duration)
{
    animation = new QPropertyAnimation(this, "pos", this);

    animation->setDuration(duration);
    animation->setStartValue(QPoint(x, 0));
    animation->setEndValue(QPoint(0 - this->width(), 0));
    
    connect(animation, &QPropertyAnimation::finished, this, [&]
            { delete this; });
}

void BulletScreenItem::startAnimal()
{
    show();
    animation->start();
}