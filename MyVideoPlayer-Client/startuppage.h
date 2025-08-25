#ifndef STARTUPPAGE_H
#define STARTUPPAGE_H

#include <QDialog>

class StartupPage : public QDialog
{
    Q_OBJECT
public:
    explicit StartupPage(QDialog *parent = nullptr);

    void startTimer();// 开启定时器
};

#endif // STARTUPPAGE_H
