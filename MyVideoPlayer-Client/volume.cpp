#include "volume.h"
#include "ui_volume.h"
#include "util.h"

Volume::Volume(QWidget *parent)
    : QWidget(parent), ui(new Ui::Volume)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Popup); // 将音量调节窗口设置为弹出窗口

    ui->volumeBox->installEventFilter(this);
}

Volume::~Volume()
{
    delete ui;
}

bool Volume::eventFilter(QObject *watched, QEvent *event)
{
    if (ui->volumeBox == watched)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            calcVolume();
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
        }
        else if (event->type() == QEvent::MouseMove)
        {
            calcVolume();
        }
        return true;
    }

    return QObject::eventFilter(watched, event);
}

void Volume::calcVolume()
{
    // 获取鼠标点击时的Y坐标，是基于屏幕的全局坐标
    int y = ui->volumeBox->mapFromGlobal(QCursor().pos()).y();
    LOG() << y;

    // 验证Y坐标的正确性，范围应在[5,150]之间
    y = y < 5 ? 5 : y;
    y = y > 150 ? 150 : y;

    // 更新 outLine的高度
    ui->outLine->setGeometry(ui->outLine->x(), y, ui->outLine->width(), 150 - y);

    // 更新 volumeBtn 的位置
    int volumeBtnY = ui->outLine->y() - ui->volumeBtn->height() / 2;
    volumeBtnY = volumeBtnY > 140 ? 140 : volumeBtnY;
    ui->volumeBtn->move(ui->volumeBtn->x(), volumeBtnY);
}