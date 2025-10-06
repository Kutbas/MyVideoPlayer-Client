#include "videoplayer.h"

#include <QApplication>
#include "startuppage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 程序启动页
    StartupPage startupPage;
    startupPage.startTimer();
    startupPage.exec();

    // 程序主界面
    VideoPlayer w;
    w.show();
    return a.exec();
}
