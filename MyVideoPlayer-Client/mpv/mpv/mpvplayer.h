#ifndef MPVPLAYER_H
#define MPVPLAYER_H

#include <QObject>
#include "./mpv/mpv/client.h"

class MpvPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MpvPlayer(QWidget *videoRenderWnd = nullptr, QObject *parent = nullptr);
    ~MpvPlayer();
    void handleMpvEvent(mpv_event *event);    // 处理 mpv 具体的事件
    void startPlay(const QString &videoPath); // 播放视频

    void play();
    void pause();
    void setPlaySpeed(double speed); // 倍速播放
    void setMute(bool isMuted);      // 设置静音
    void setVolume(int64_t volume);  // 设置音量

private slots:
    void onMpvEvents();
signals:
    void mpvEvents();                          // 当 mpv 触发事件时，在回调函数中发射该信号，由用户程序处理 mpv 的事件
    void playPositionChanged(int64_t seconds); // 通知界面更新当前时间

private:
    mpv_handle *mpv = nullptr;
};

#endif // MPVPLAYER_H
