#ifndef PAGESWITCHBUTTON_H
#define PAGESWITCHBUTTON_H

#include <QPushButton>
#include <QLabel>

class PageSwitchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PageSwitchButton(QWidget *parent = nullptr);

    void setImageAndText(const QString &imagePath, const QString &text, int pageId); // 设置图片和文本
    void setTextColor(const QString &textColor);                                     // 设置文本的颜色
    int getPageId() const;                                                           // 获取页面索引
    void setImage(const QString &imagePath);                                         // 设置按钮图片

private:
    void mousePressEvent(QMouseEvent *event);

private:
    QLabel *btnImage;  // 按钮上的图片
    QLabel *btnTittle; // 按钮上的文本
    int pageId;        // 按钮对应的页面索引

signals:
    void switchPage(int pageId); // 切换页面的信号
};

#endif // PAGESWITCHBUTTON_H
