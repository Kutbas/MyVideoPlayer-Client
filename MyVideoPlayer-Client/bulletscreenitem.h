#ifndef BULLETSCREENITEM_H
#define BULLETSCREENITEM_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPropertyAnimation>

class BulletScreenInfo
{
public:
    QString userId;   // 发送弹幕用户
    QString videoId;  // 弹幕对应的视频Id
    int64_t playTime; // 发送弹幕时当前播放时间
    QString text;     // 弹幕内容

    BulletScreenInfo(const QString &userId = "", int64_t playTime = 0,
                     const QString &text = "")
        : userId(userId), playTime(playTime), text(text)
    {
    }
};

class BulletScreenItem : public QFrame
{
    Q_OBJECT
public:
    explicit BulletScreenItem(QWidget *parent = nullptr);

    void setBulletScreenText(const QString &text); // 设置弹幕中的文本
    void setBulletScreenIcon(QPixmap &pixmap);     // 设置弹幕中的头像

    void setBulletScreenAnimation(int x, int duration); // 给弹幕添加动画
    void startAnimation();                           // 开启动画

private:
    QLabel *textLabel;             // 弹幕文本
    QLabel *imageLabel;            // 弹幕中的头像
    QPropertyAnimation *animation; // 动画类指针
};

#endif // BULLETSCREENITEM_H
