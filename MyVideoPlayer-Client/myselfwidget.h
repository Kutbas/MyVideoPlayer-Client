#ifndef MYSELFWIDGET_H
#define MYSELFWIDGET_H

#include <QWidget>

namespace Ui
{
    class MyselfWidget;
}

class MyselfWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyselfWidget(QWidget *parent = nullptr);
    ~MyselfWidget();

private:
    void initUI();

private slots:
    void onAvatarBtnClicked();
    void onSettingBtnClicked();
    void onUploadVideoBtnClicked();

signals:
    void switchUploadVideoPage(int pageIndex);

private:
    Ui::MyselfWidget *ui;
};

#endif // MYSELFWIDGET_H
