#include "mpvplayer.h"
#include "util.h"
#include <QWidget>

static void wakeup(void *ctx)
{
    MpvPlayer *mpv = (MpvPlayer *)ctx;
    emit mpv->mpvEvents();
}

MpvPlayer::MpvPlayer(QWidget *videoRenderWnd, QObject *parent)
    : QObject{parent}
{
    // 设置程序的区域
    // LC_NUMERIC：设置数字格式，包括小数点和千分位符
    // "C"：表示使用 C 标准的默认区域设置
    std::setlocale(LC_NUMERIC, "C");

    // 创建 mpv 实例
    mpv = mpv_create();
    if (nullptr == mpv)
    {
        LOG() << "mpv 实例创建失败！";
        return;
    }

    // 设置视频的渲染窗口，将 wid 告知给 mpv
    int64_t wid = videoRenderWnd->winId();
    mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

    // 设置 mpv 事件触发时的回调函数
    mpv_set_wakeup_callback(mpv, wakeup, this);

    connect(this, &MpvPlayer::mpvEvents, this, &MpvPlayer::onMpvEvents);

    // 初始化 mpv 的实例
    if (mpv_initialize(mpv) < 0)
    {
        LOG() << "mpv 初始化失败！";
        mpv_destroy(mpv);
        return;
    }
}

MpvPlayer::~MpvPlayer()
{
    if (mpv)
        mpv_terminate_destroy(mpv);
}

void MpvPlayer::onMpvEvents()
{
    // 循环处理所有的事件，直到 mpv 事件队列为空
    while (mpv)
    {
        mpv_event *event = mpv_wait_event(mpv, 0);

        if (MPV_EVENT_NONE == event->event_id)
            break;

        // 获取到具体的事件，处理该事件
        handleMpvEvent(event);
    }
}

void MpvPlayer::handleMpvEvent(mpv_event *event)
{
    switch (event->event_id)
    {
    case MPV_EVENT_SHUTDOWN:
    {
        mpv_terminate_destroy(mpv);
        mpv = nullptr;
        break;
    }

    default:
        break;
    }
}

void MpvPlayer::startPlay(const QString &videoPath)
{
    // 发送加载视频的命令，播放视频
    const QByteArray fileName = videoPath.toLocal8Bit();
    const char *args[] = {
        "loadfile", fileName.data(), NULL};
    mpv_command_async(mpv, 0, args);
}

void MpvPlayer::play()
{
    int pause = 0;
    mpv_set_property_async(mpv, 0, "pause", MPV_FORMAT_FLAG, &pause);
}

void MpvPlayer::pause()
{
    int pause = 1;
    mpv_set_property_async(mpv, 0, "pause", MPV_FORMAT_FLAG, &pause);
}

void MpvPlayer::setPlaySpeed(double speed)
{
    mpv_set_property_async(mpv, 0, "speed", MPV_FORMAT_DOUBLE, &speed);
}

void MpvPlayer::setMute(bool isMuted)
{
    int flag = isMuted ? 1 : 0;
    mpv_set_property_async(mpv, 0, "mute", MPV_FORMAT_FLAG, &flag);
}