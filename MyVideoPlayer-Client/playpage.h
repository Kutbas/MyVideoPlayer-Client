#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include "volume.h"
#include "playspeed.h"
#include "./mpv/mpv/mpvplayer.h"
#include <QDialog>
#include <QFrame>

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
    void setPlayProgress(double playRatio); // 设置播放进度

private:
    void moveWindows(const QPoint &point);
    QString secondToTime(int64_t seconds);
    void initBarrageArea(); // 布局弹幕主窗口

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
};

#endif // PLAYPAGE_H
