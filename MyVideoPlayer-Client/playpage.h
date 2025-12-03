#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include "volume.h"
#include "playspeed.h"
#include "./mpv/mpv/mpvplayer.h"
#include <QDialog>
#include <QFrame>
#include "bulletscreenitem.h"

namespace Ui
{
    class PlayPage;
}

class PlayPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayPage(QWidget *parent = nullptr);
    ~PlayPage();

    void mousePressEvent(QMouseEvent *event); // 鼠标点击
    void mouseMoveEvent(QMouseEvent *event);  // 鼠标移动
    void startPlaying(const QString &videoPath);

private slots:
    void onVolumeBtnClicked();
    void onSpeedBtnClicked();
    void onLikeImageBtnClicked();
    void onPlayBtnClicked();
    void onPlaySpeedChanged(double speed); // 倍速播放
    void setVolume(int volume);            // 音量调节
    void onPlayPositionChanged(int64_t playTime);
    void setPlayProgress(double playRatio);                 // 设置播放进度
    void onBulletScreenBtnClicked();                        //  弹幕开关控制
    void onSendBulletScreenBtnClicked(const QString &text); // 发射弹幕

private:
    void moveWindows(const QPoint &point);
    QString secondToTime(int64_t seconds);

    void initBarrageArea();       // 布局弹幕主窗口
    void buildBulletScreenData(); // 构造弹幕数据
    void showBulletScreen();      // 显示弹幕

private:
    Ui::PlayPage *ui;
    QPoint dragPos;
    Volume *volume;
    PlaySpeed *playSpeed;

    MpvPlayer *mpvPlayer = nullptr;
    bool isPlay = false;  // 默认视频为暂停状态
    int64_t playTime = 0; // 当前播放时长
    QString videoPath;

    // 弹幕相关的成员
    QDialog *barrageArea;
    QFrame *top;
    QFrame *middle;
    QFrame *bottom;
    // key：视频当前播放时间
    // value：当前播放时间下所有的弹幕数据
    QMap<int64_t, QList<BulletScreenInfo>> bulletScreens;
    bool isStartBS = true; // 是否开启弹幕，默认弹幕开启
};

#endif // PLAYPAGE_H
