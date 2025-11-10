#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QWidget>
#include <QPushButton>

class PageButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PageButton(int pageNum = 1, QWidget *parent = nullptr);
    void setActive(bool active);
    bool getActive() const;

    void setFolded(bool folded);
    bool getFolded() const;

    void setPage(int pageNum);
    int getPage() const;

private:
    int pageNum;              // 页号
    bool isActiveBtn = false; // 按钮是否被点击
    bool isFoldedBtn = false; // 按钮是否被折叠
};

#endif // PAGEBUTTON_H
