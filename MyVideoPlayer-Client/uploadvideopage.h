#ifndef UPLOADVIDEOPAGE_H
#define UPLOADVIDEOPAGE_H

#include <QWidget>

namespace Ui
{
    class UploadVideoPage;
}

class UploadVideoPage : public QWidget
{
    Q_OBJECT

public:
    explicit UploadVideoPage(QWidget *parent = nullptr);
    ~UploadVideoPage();

private slots:
    void onCommitBtnClicked();

signals:
    void switchMyselfPage(int pageId);

private:
    Ui::UploadVideoPage *ui;
};

#endif // UPLOADVIDEOPAGE_H
