#ifndef VIDEOBOX_H
#define VIDEOBOX_H

#include <QWidget>
#include "playpage.h"

namespace Ui
{
    class VideoBox;
}

class VideoBox : public QWidget
{
    Q_OBJECT

public:
    explicit VideoBox(QWidget *parent = nullptr);
    ~VideoBox();

    bool eventFilter(QObject *watched, QEvent *event);

private:
    void onPlayClicked();

private:
    Ui::VideoBox *ui;
    PlayPage *playPage;
};

#endif // VIDEOBOX_H
