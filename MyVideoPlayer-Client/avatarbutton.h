#ifndef AVATARBUTTON_H
#define AVATARBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class AvatarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AvatarButton(QWidget *parent = nullptr);
    void changeMode(bool isShow);

private:
    void enterEvent(QEnterEvent *event); // 鼠标进入
    void leaveEvent(QEvent *event);      // 鼠标离开

private:
    QLabel *mask; // 遮罩层
    bool isShow;  // 是否显示遮罩层

signals:
};

#endif // AVATARBUTTON_H
