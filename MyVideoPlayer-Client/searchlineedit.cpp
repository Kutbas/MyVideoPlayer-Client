#include "searchlineedit.h"
#include "util.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    // // 设置编辑框的尺寸
    // setFixedSize(320, 36);
    // setPlaceholderText("请搜索你感兴趣的视频");
    // setTextMargins(33, 0, 0, 0);
    // setObjectName("search");
    // setStyleSheet("#search{"
    //               "background-color : #FFFFFF;"
    //               "border-radius : 18px;"
    //               "border : 1px solid #3ECEFE;"
    //               "font-family : 微软雅黑;"
    //               "font-size : 14px;"
    //               "font-style : normal;}");

    // // 搜索的图片
    // QLabel *searchImage = new QLabel(this);
    // searchImage->setFixedSize(16, 16);
    // searchImage->setPixmap(QPixmap(":/images/homePage/sousuo.png"));

    // // 确认按钮
    // QPushButton *searchBtn = new QPushButton(this);
    // searchBtn->setText("搜索");
    // searchBtn->setFixedSize(62, 32);
    // searchBtn->setStyleSheet("background-color : #3ECEFE;"
    //                          "border-radius : 16px;"
    //                          "font-family : 微软雅黑;"
    //                          "font-size : 14px;"
    //                          "color : #FFFFFF;"
    //                          "font-style : normal;");

    // // 将图片和按钮放到水平布局器中
    // QHBoxLayout *layout = new QHBoxLayout(this);
    // layout->addWidget(searchImage);
    // layout->addStretch();
    // layout->addWidget(searchBtn);
    // layout->setContentsMargins(11, 0, 2, 0);

    QWidget *searchWidget = new QWidget(parent);
    searchWidget->setObjectName("search");
    searchWidget->setFixedSize(320, 36);
    searchWidget->setStyleSheet("#search{"
                                "background-color:#FFFFFF;"
                                "border-radius:18px;"
                                "border:1px solid #3ECEFE;"
                                "font-family:微软雅黑;"
                                "font-size:14px;}");

    // 搜索框
    QLineEdit *lineEdit = new QLineEdit(searchWidget);
    lineEdit->setPlaceholderText("请搜索你感兴趣的视频");
    lineEdit->setStyleSheet("border:none;");
    // "background-color:red;"

    // 搜索按钮
    QPushButton *searchBtn = new QPushButton("搜索", searchWidget);
    searchBtn->setFixedSize(62, 32);
    searchBtn->setStyleSheet("background-color:#3ECEFE;"
                             "border-radius:16px;"
                             "font-family:微软雅黑;"
                             "font-size:14px;"
                             "color:#FFFFFF;");

    // 图标
    QLabel *searchImage = new QLabel(searchWidget);
    searchImage->setPixmap(QPixmap(":/images/homePage/sousuo.png"));
    searchImage->setFixedSize(16, 16);

    // 布局
    QHBoxLayout *layout = new QHBoxLayout(searchWidget);
    layout->addWidget(searchImage);
    layout->addWidget(lineEdit);
    layout->addWidget(searchBtn);
    layout->setContentsMargins(11, 0, 2, 0);

    connect(searchBtn, &QPushButton::clicked, this, &SearchLineEdit::onSearchBtnClicked);
    connect(this, &QLineEdit::returnPressed, this, &SearchLineEdit::onSearchBtnClicked);
}

void SearchLineEdit::onSearchBtnClicked()
{
    LOG() << "搜索按钮点击";
}