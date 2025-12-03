#ifndef BARRAGEEDIT_H
#define BARRAGEEDIT_H

#include <QLineEdit>
#include <QPushButton>

class BarrageEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit BarrageEdit(QWidget *parent = nullptr);

private slots:
    void onSendBsBtnClicked();

signals:
    void sendBulletScreen(const QString &text); // 通知 PlayPage 发送该条弹幕

private:
    QPushButton *sendBsBtn;
};

#endif // BARRAGEEDIT_H
