#include "barrageedit.h"
#include "util.h"

BarrageEdit::BarrageEdit(QWidget *parent)
    : QLineEdit{parent}
{
    // 设置弹幕编辑框的属性
    setFixedSize(1030, 32);
    setPlaceholderText("这个视频在说什么？");
    setMaxLength(30); // 最多支持输入30个字符
    setTextMargins(12, 6, 0, 7);
    setStyleSheet("font-family : 微软雅黑;"
                  "font-size : 14px;"
                  "background-color : #4D4D4D;"
                  "color : #DEDEDE;"
                  "border : none;"
                  "border-radius : 4px;");

    // 初始化发送按钮
    sendBsBtn = new QPushButton(this);
    sendBsBtn->setFixedSize(58, 28);
    sendBsBtn->setText("发送");
    sendBsBtn->setCursor(QCursor(Qt::ArrowCursor));
    sendBsBtn->setStyleSheet("background-color : #3ECEFE;"
                             "color : #FFFFFF;"
                             "border-radius : 4px;"
                             "font-family : 微软雅黑;"
                             "font-size : 14px;");

    // 把按钮移动到合适的位置
    sendBsBtn->move(width() - sendBsBtn->width() - 2, 2);

    connect(sendBsBtn, &QPushButton::clicked, this, &BarrageEdit::onSendBsBtnClicked);
}

void BarrageEdit::onSendBsBtnClicked()
{
    // LOG() << "发送弹幕：" << text();
    emit sendBulletScreen(text());
}
