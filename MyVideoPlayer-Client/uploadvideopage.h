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
    void onLineEditTextChanged(const QString &text);
    void onPlainEditTextChanged();
    void onChangeButtonClicked();
    void onUpdateTags(const QString &kind); // QComboBox 中选择项发生变化时对应的槽函数
    void addTagsByKind(const QString &kind); // 将kind下标签以按钮形式展示在界面上

signals:
    void switchMyselfPage(int pageId);

private:
    Ui::UploadVideoPage *ui;
};

#endif // UPLOADVIDEOPAGE_H
