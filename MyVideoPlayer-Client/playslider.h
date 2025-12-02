#ifndef PLAYSLIDER_H
#define PLAYSLIDER_H

#include <QWidget>

namespace Ui
{
    class PlaySlider;
}

class PlaySlider : public QWidget
{
    Q_OBJECT

public:
    explicit PlaySlider(QWidget *parent = nullptr);
    ~PlaySlider();
    void setPlayStep(double stepRatio); // 设置播放进度

private:
    void mousePressEvent(QMouseEvent *event);   // 鼠标点击
    void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放
    void mouseMoveEvent(QMouseEvent *event);    // 鼠标移动
    void moveSlider();                          // 进度条移动

signals:
    void setPlayProgress(double playRatio); // 设置播放进度信号

private:
    Ui::PlaySlider *ui;
    int playProgress; // 记录视频当前的播放进度
};

#endif // PLAYSLIDER_H
