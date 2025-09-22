#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include "volume.h"

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

private slots:
    void onVolumeBtnClicked();

private:
    void moveWindows(const QPoint &point);

private:
    Ui::PlayPage *ui;
    QPoint dragPos;
    Volume *volume;
};

#endif // PLAYPAGE_H
