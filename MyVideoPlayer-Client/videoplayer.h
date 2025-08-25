#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class VideoPlayer;
}
QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

private:
    Ui::VideoPlayer *ui;
};
#endif // VIDEOPLAYER_H
