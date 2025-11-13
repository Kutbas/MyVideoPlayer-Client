#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QDialog>

class Toast : public QDialog
{
    Q_OBJECT
public:
    Toast(const QString &text);                  // 仅显示文本
    Toast(const QString &text, QWidget *widget); // 文本显示结束后，显示窗口

    static void showMessage(const QString &text);
    static void showMessage(const QString &text, QWidget *widget);

private:
    void initUI(const QString &text);
};

#endif // TOAST_H
