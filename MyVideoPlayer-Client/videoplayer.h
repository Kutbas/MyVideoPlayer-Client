#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class VideoPlayer;
}
QT_END_NAMESPACE

enum StackedWidgetPage
{
    HomePage,
    MyPage,
    AdminPage,
    UploadPage
};

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    ~VideoPlayer();
    static VideoPlayer *getInstance();

private slots:
    void onSwitchPage(int pageId);

private:
    VideoPlayer(QWidget *parent = nullptr);

    void initUI();                            // 初始化界面UI
    void connectSignalAndSlot();              // 绑定信号槽
    void mousePressEvent(QMouseEvent *event); // 鼠标单击
    void mouseMoveEvent(QMouseEvent *event);  // 鼠标移动
    void resetSwitchBtnInfo(int pageId);      // 重置页面按钮信息
private:
    Ui::VideoPlayer *ui;
    QPoint dragPos;
    static VideoPlayer *instance;
};
#endif // VIDEOPLAYER_H
