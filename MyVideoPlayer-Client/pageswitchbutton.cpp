#include "pageswitchbutton.h"
#include "util.h"

PageSwitchButton::PageSwitchButton(QWidget *parent)
    : QPushButton{parent}
{
    setFixedSize(48, 46); // 设置按钮的大小

    btnImage = new QLabel(this);
    btnImage->setGeometry(12, 0, 24, 24); // 设置图片的位置和大小

    btnTittle = new QLabel(this);
    btnTittle->setGeometry(0, 30, 48, 16);    // 设置文本的位置和大小
    btnTittle->setAlignment(Qt::AlignCenter); // 设置文本居中对齐

    setStyleSheet("border:none;"); // 去掉按钮边框
}

// 设置图片和文本
void PageSwitchButton::setImageAndText(const QString &imagePath, const QString &text, int pageId)
{
    setImage(imagePath);
    btnTittle->setText(text);
    this->pageId = pageId;
}

// 鼠标单击
void PageSwitchButton::mousePressEvent(QMouseEvent *event)
{
    (void *)event;
    setTextColor("#000000"); // 切换选中的按钮为黑色
    emit switchPage(pageId); // 发送切换页面的信号
    LOG() << pageId << "被点击了";
}

// 设置文本颜色
void PageSwitchButton::setTextColor(const QString &textColor)
{
    btnTittle->setStyleSheet("font-family:微软雅黑;"
                             "font-size:12px;"
                             "font-weight:bold;"
                             "color:" +
                             textColor + ";");
}

// 获取页面索引
int PageSwitchButton::getPageId() const
{
    return pageId;
}

// 设置按钮图片
void PageSwitchButton::setImage(const QString &imagePath)
{
    btnImage->setPixmap(QPixmap(imagePath));
}