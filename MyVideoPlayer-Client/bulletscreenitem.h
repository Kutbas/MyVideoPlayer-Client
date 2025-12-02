#ifndef BULLETSCREENITEM_H
#define BULLETSCREENITEM_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPropertyAnimation>

class BulletScreenItem : public QFrame
{
    Q_OBJECT
public:
    explicit BulletScreenItem(QWidget *parent = nullptr);

    void setBulletScreenText(const QString &text); // 设置弹幕中的文本
    void setBulletScreenIcon(QPixmap &pixmap);     // 设置弹幕中的头像

    void setBulletScreenAnimal(int x, int duration); // 给弹幕添加动画
    void startAnimal();                              // 开启动画

private:
    QLabel *textLabel;             // 弹幕文本
    QLabel *imageLabel;            // 弹幕中的头像
    QPropertyAnimation *animation; // 动画类指针
};

#endif // BULLETSCREENITEM_H
