#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>

namespace Ui
{
    class Volume;
}

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();

signals:
    void setVolume(int volumeRatio); //该信号通知 PlayPage 页面，完成音量调节设置

private:
    bool eventFilter(QObject *watched, QEvent *event);
    void calcVolume();

private:
    Ui::Volume *ui;
    int volumeRatio; // 保存音量数值
};

#endif // VOLUME_H
