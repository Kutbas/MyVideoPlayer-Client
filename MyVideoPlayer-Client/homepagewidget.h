#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui
{
    class HomePageWidget;
}

class HomePageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageWidget(QWidget *parent = nullptr);
    ~HomePageWidget();

private:
    void initKindAndTags(); // 初始化分类和标签
    QPushButton *buildSelectBtn(QWidget *parent, const QString &color, const QString &text);
    void resetTags(const QList<QString> &tags); // 重置标签
    void initRefreshAndTopBtn();                // 初始化刷新和置顶按钮;
    void initVideos();

private slots:
    void onKindBtnClicked(QPushButton *clickedKindBtn); // 分类按钮点击
    void onTagBtnClicked(QPushButton *clickedTagBtn);   // 标签按钮点击
    void onTopBtnClicked();                             // 置顶按钮点击
    void onRefreshBtnClicked();                         // 刷新按钮点击

private:
    Ui::HomePageWidget *ui;
};

#endif // HOMEPAGEWIDGET_H
