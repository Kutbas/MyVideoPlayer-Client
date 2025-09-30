#include "avatarbutton.h"

AvatarButton::AvatarButton(QWidget *parent)
    : QPushButton{parent},
      isShow(true)
{
    mask = new QLabel(this);
    mask->setObjectName("maskLabel");
    mask->setGeometry(0, 0, 60, 60);
    mask->setStyleSheet("#mask{"
                        "color:#FFFFFF;"
                        "background-color:rgba(0,0,0,0.5);"
                        "border-radius:30px;}");
    mask->setText("修改图像");
    mask->setAlignment(Qt::AlignCenter);
    mask->hide();
}
// 鼠标进入
void AvatarButton::enterEvent(QEnterEvent *event)
{
    (void *)event;
    if (isShow)
    {
        mask->show();
    }
}

// 鼠标离开
void AvatarButton::leaveEvent(QEvent *event)
{
    (void *)event;
    mask->hide();
}

void AvatarButton::changeMode(bool isShow)
{
    this->isShow = isShow;
}
