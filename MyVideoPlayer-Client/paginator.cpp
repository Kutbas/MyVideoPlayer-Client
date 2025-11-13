#include "paginator.h"
#include <QHBoxLayout>
#include <QLabel>

Paginator::Paginator(int pageCount, QWidget *parent)
    : QWidget{parent}
{
    this->pageCount = pageCount;

    // 设置页面尺寸
    setMinimumSize(1270, 32);

    // 创建水平布局器
    QHBoxLayout *layout = new QHBoxLayout();
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 3, 0);
    layout->setSpacing(8);

    // 创建上一页按钮
    prevPageBtn = new QPushButton();
    prevPageBtn->setIcon(QIcon(":/images/admin/arrow-left.png"));
    setBtnStyle(prevPageBtn);

    // 创建下一页按钮
    nextPageBtn = new QPushButton();
    nextPageBtn->setIcon(QIcon(":/images/admin/arrow-right.png"));
    setBtnStyle(nextPageBtn);

    // 创建中间页面按钮
    if (pageCount <= 7)
    {
        // 不需要折叠按钮，默认从第一页开始显示
        for (int i = 1; i <= pageCount; i++)
        {
            PageButton *pageBtn = new PageButton(i);
            if (1 == i)
                pageBtn->setActive(true);

            pageBtns.append(pageBtn);
        }
    }
    else
    {
        // 超过7页，前5个页面按钮上显示1~5数字
        for (int i = 1; i <= 5; i++)
        {
            PageButton *pageBtn = new PageButton(i);
            if (1 == i)
                pageBtn->setActive(true);

            pageBtns.append(pageBtn);
        }

        // 折叠按钮
        PageButton *foldedBtn = new PageButton(0);
        foldedBtn->setFolded(true);
        pageBtns.push_back(foldedBtn);

        // 添加最后一页按钮
        PageButton *lastPageBtn = new PageButton(pageCount);
        pageBtns.push_back(lastPageBtn);
    }

    // 创建输入页号的编辑框
    pageEdit = new QLineEdit();
    pageEdit->setFixedSize(QSize(48, 32));
    pageEdit->setAlignment(Qt::AlignCenter);
    pageEdit->setStyleSheet("QLineEdit{"
                            "background-color: #FFFFFF; "
                            "border: 1px solid #D9D9D9; "
                            "border-radius: 2px; }");

    QLabel *jumpToLabel = new QLabel("跳至");
    QLabel *pageLabel = new QLabel("页");

    // 将元素添加到布局器中
    layout->addStretch(); // 在最左侧添加一个空白区域

    layout->addWidget(prevPageBtn);
    for (int i = 0; i < pageBtns.size(); i++)
    {
        layout->addWidget(pageBtns[i]);
    }
    layout->addWidget(nextPageBtn);

    layout->addWidget(jumpToLabel);
    layout->addWidget(pageEdit);
    layout->addWidget(pageLabel);

    initSignalAndSlots();
}

void Paginator::setBtnStyle(QPushButton *btn)
{
    btn->setFixedSize(QSize(32, 32));
    btn->setIconSize(QSize(12, 12));
    btn->setStyleSheet("QPushButton {"
                       "color: #000000; "
                       "background-color: #FFFFFF; "
                       "border: 1px solid #D9D9D9; "
                       "border-radius: 2px;}");
}

void Paginator::jumpToPage(int pageNum)
{
    if (pageNum < 1 || pageNum > pageCount)
        return;
    // 页数不超过7页，直接设置选中指定按钮
    if (pageCount <= 7)
    {
        for (auto *pageBtn : pageBtns)
            pageBtn->setActive(false);

        pageBtns[currentPage - 1]->setActive(true);
        currentPage = pageNum;
    }
    // 页数超过7页
    else
    {
        if (pageNum <= 5)
            jumpToPageCase1(pageNum);
        else if (pageNum >= pageCount - 4)
            jumpToPageCase2(pageNum);
        else
            jumpToPageCase3(pageNum);
        currentPage = pageNum;
    }

    // 发送信号
    // emit this->pageChanged(currentPage);
}

void Paginator::jumpToPageCase1(int pageNum)
{
    // pageNum <= 5 的情况
    // 固定7个按钮, 前5个按钮显示数字
    // 第6个按钮时折叠按钮，最后1个按钮显示最后1页

    pageBtns[0]->setPage(1);
    pageBtns[1]->setPage(2);
    pageBtns[2]->setPage(3);
    pageBtns[3]->setPage(4);
    pageBtns[4]->setPage(5);
    pageBtns[5]->setPage(6);
    pageBtns[6]->setPage(pageCount);

    // 处理激活状态和折叠状态
    for (int i = 0; i < pageBtns.size(); i++)
    {
        // 设置当前显示页号对应的按钮为激活状态
        if (pageBtns[i]->getPage() == pageNum)
            pageBtns[i]->setActive(true);
        else
            pageBtns[i]->setActive(false);

        // 将第6个按钮折叠
        if (i == 5)
            pageBtns[i]->setFolded(true);
        else
            pageBtns[i]->setFolded(false);
    }
}

void Paginator::jumpToPageCase2(int pageNum)
{
    // pageNum >= pageCount - 4 的情况
    // 固定7个按钮, 第1个显示第1页，第2个为折叠按钮
    pageBtns[0]->setPage(1);
    pageBtns[1]->setPage(pageCount - 5);
    pageBtns[2]->setPage(pageCount - 4);
    pageBtns[5]->setPage(pageCount - 1);
    pageBtns[3]->setPage(pageCount - 3);
    pageBtns[4]->setPage(pageCount - 2);
    pageBtns[6]->setPage(pageCount);

    // 处理激活状态和折叠状态
    for (int i = 0; i < pageBtns.size(); i++)
    {
        // 设置当前显示页号对应的按钮为激活状态
        if (pageBtns[i]->getPage() == pageNum)
            pageBtns[i]->setActive(true);
        else
            pageBtns[i]->setActive(false);

        // 将第1个按钮折叠
        if (i == 1)
            pageBtns[i]->setFolded(true);
        else
            pageBtns[i]->setFolded(false);
    }
}

void Paginator::jumpToPageCase3(int pageNum)
{
    // 2个折叠按钮
    // 用中间按钮, 下标3表示当前页面
    pageBtns[0]->setPage(1);
    pageBtns[1]->setPage(pageNum - 2);
    pageBtns[2]->setPage(pageNum - 1);
    pageBtns[3]->setPage(pageNum);
    pageBtns[4]->setPage(pageNum + 1);
    pageBtns[5]->setPage(pageNum + 2);
    pageBtns[6]->setPage(pageCount);

    for (int i = 0; i < pageBtns.size(); i++)
    {
        // 处理激活状态, 中间按钮激活
        if (i == 3)
            pageBtns[i]->setActive(true);
        else
            pageBtns[i]->setActive(false);

        // 处理折叠状态, 下标为1和5的按钮折叠
        if (i == 1 || i == 5)
            pageBtns[i]->setFolded(true);
        else
            pageBtns[i]->setFolded(false);
    }
}

void Paginator::initSignalAndSlots()
{
    // 绑定上一页和下一页的信号槽
    connect(prevPageBtn, &QPushButton::clicked, this, &Paginator::prevPage);
    connect(nextPageBtn, &QPushButton::clicked, this, &Paginator::nextPage);

    // 绑定页面按钮的信号槽
    for (auto *pageBtn : pageBtns)
        connect(pageBtn, &QPushButton::clicked, this, &Paginator::pageBtnClicked);

    // 绑定编辑框信号槽，编辑框输入完成之后回车
    connect(pageEdit, &QLineEdit::returnPressed, this, [=]()
            {
        int pageNum = pageEdit->text().toInt();
        if(pageNum < 1)
                pageNum = 1;
        if(pageNum > pageCount)
                pageNum = pageCount;
        jumpToPage(pageNum); });
}

void Paginator::prevPage()
{
    if (currentPage == 1)
        return;
    jumpToPage(currentPage - 1);
}

void Paginator::nextPage()
{
    if (currentPage == pageCount)
        return;
    jumpToPage(currentPage + 1);
}

void Paginator::pageBtnClicked()
{
    // 获取触发该信号的按钮
    int page = static_cast<PageButton *>(sender())->getPage();
    jumpToPage(page);
}