#include "pagebutton.h"

PageButton::PageButton(int pageNum, QWidget *parent) : QPushButton(parent)
{
    this->pageNum = pageNum;

    // 设置按钮尺寸以及图标的尺寸
    setFixedSize(32, 32);
    setIconSize(QSize(16, 16));

    // 设置按钮上的文本
    if (isFoldedBtn)
    {
        setText("...");
    }
    else
    {
        setText(QString::number(pageNum));
    }

    // 设置按钮的选中状态
    setActive(isActiveBtn);
}

void PageButton::setActive(bool active)
{
    this->isActiveBtn = active;
    if (active)
    {
        this->setStyleSheet("QPushButton {"
                            "color: #FFFFFF; "
                            "background-color: #3ECEFE; "
                            "border: 1px solid #3ECEFE; "
                            "border-radius: 2px;}");
    }
    else
    {
        this->setStyleSheet("QPushButton {"
                            "color: #000000; "
                            "background-color: #FFFFFF; "
                            "border: 1px solid #D9D9D9; "
                            "border-radius: 2px;}");
    }
}

bool PageButton::getActive() const
{
    return isActiveBtn;
}

void PageButton::setFolded(bool folded)
{
    this->isFoldedBtn = folded;
    if (folded)
    {
        this->setText("...");
    }
    else
    {
        this->setText(QString::number(pageNum));
    }
}

bool PageButton::getFolded() const
{
    return isFoldedBtn;
}

void PageButton::setPage(int pageNum)
{
    this->pageNum = pageNum;
    this->setText(QString::number(pageNum));
}

int PageButton::getPage() const
{
    return pageNum;
}
