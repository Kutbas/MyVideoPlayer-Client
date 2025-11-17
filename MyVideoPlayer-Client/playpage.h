#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include "volume.h"
#include "playspeed.h"
#include "./mpv/mpv/mpvplayer.h"

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
    void onPlaySpeedChanged(double speed);

private:
    void moveWindows(const QPoint &point);

private:
    Ui::PlayPage *ui;
    QPoint dragPos;
    Volume *volume;
    PlaySpeed *playSpeed;

    MpvPlayer *mpvPlayer = nullptr;
    bool isPlay = false; // 默认视频为暂停状态
};

#endif // PLAYPAGE_H
